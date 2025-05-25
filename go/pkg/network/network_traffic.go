package network

import (
	"code/utils"
	"fmt"
	"net"
	"runtime"
	"sync"
	"sync/atomic"
	"time"

	"github.com/google/gopacket"
	"github.com/google/gopacket/afpacket"
	"github.com/google/gopacket/layers"
	"github.com/google/gopacket/pcap"
	"golang.org/x/net/bpf"
)

// 流量统计项
type TrafficStats struct {
	ToInternal   uint64 // 访问内网流量
	FromInternal uint64 // 来自内网的流量
	ToExternal   uint64 // 访问外网流量
	FromExternal uint64 // 来自外网的流量
}

// 流量统计管理器
type TrafficManager struct {
	stats      map[string]*TrafficStats // IP地址到统计数据的映射
	ipSet      map[string]struct{}      // 关注的IP集合
	mu         sync.RWMutex             // 读写锁保护共享数据
	stopCh     chan struct{}
	wg         sync.WaitGroup // 等待协程完成
	flushTimer *time.Timer    // 定期刷新统计数据的计时器
	lockMap    map[string]*sync.Mutex
}

// 创建新的流量管理器
func NewTrafficManager(ifaceName, syntax string,
	flushInterval time.Duration) *TrafficManager {
	tm := &TrafficManager{
		stopCh:  make(chan struct{}),
		stats:   make(map[string]*TrafficStats),
		ipSet:   make(map[string]struct{}),
		lockMap: make(map[string]*sync.Mutex),
	}

	// 启动流量统计处理协程
	for i := 0; i < runtime.NumCPU(); i++ {
		tm.wg.Add(1)
		go tm.capture(ifaceName, syntax)
	}
	// 设置定期刷新计时器
	if flushInterval > 0 {
		tm.flushTimer = time.AfterFunc(flushInterval, func() {
			tm.FlushStats()
			// 重新设置计时器
			tm.flushTimer.Reset(flushInterval)
		})
	}
	return tm
}

// 添加关注的IP地址
func (tm *TrafficManager) AddIP(ip string) {
	tm.mu.Lock()
	defer tm.mu.Unlock()
	tm.ipSet[ip] = struct{}{}

	if _, ok := tm.lockMap[ip]; !ok {
		tm.lockMap[ip] = &sync.Mutex{}
	}
}

// 更新统计数据
// 更新统计数据
func (tm *TrafficManager) updateStats(srcIP, dstIP net.IP, length uint32) {
	srcIPStr := srcIP.String()
	dstIPStr := dstIP.String()
	length64 := uint64(length)

	// 检查源IP是否在内网
	srcIsInternal := utils.IsInternalIP(srcIP)
	// 检查目的IP是否在内网
	dstIsInternal := utils.IsInternalIP(dstIP)

	// 检查是否需要统计此IP
	tm.mu.RLock()
	_, srcWatched := tm.ipSet[srcIPStr]
	_, dstWatched := tm.ipSet[dstIPStr]
	tm.mu.RUnlock()

	// 更新源IP的统计（如果关注）
	if srcWatched {
		lock := tm.lockMap[srcIPStr]
		lock.Lock()
		if _, exists := tm.stats[srcIPStr]; !exists {
			tm.stats[srcIPStr] = &TrafficStats{}
		}
		stats := tm.stats[srcIPStr]

		if srcIsInternal && !dstIsInternal {
			atomic.AddUint64(&stats.ToExternal, length64) // 访问外网的流量
		} else if srcIsInternal && dstIsInternal {
			atomic.AddUint64(&stats.ToInternal, length64) // 访问内网的流量
		}
		lock.Unlock()
	}

	// 更新目的IP的统计（如果关注）
	if dstWatched {
		lock := tm.lockMap[dstIPStr]
		lock.Lock()
		if _, exists := tm.stats[dstIPStr]; !exists {
			tm.stats[dstIPStr] = &TrafficStats{}
		}
		stats := tm.stats[dstIPStr]

		if !srcIsInternal && dstIsInternal {
			atomic.AddUint64(&stats.FromExternal, length64) // 来自外网的流量
		} else if srcIsInternal && dstIsInternal {
			atomic.AddUint64(&stats.FromInternal, length64) // 来自内网的流量
		}
		lock.Unlock()
	}
}

// 获取特定IP的统计数据
func (tm *TrafficManager) GetStats(ip string) (*TrafficStats, bool) {
	tm.mu.RLock()
	defer tm.mu.RUnlock()
	stats, exists := tm.stats[ip]
	return stats, exists
}

// 获取所有IP的统计数据
func (tm *TrafficManager) GetAllStats() map[string]*TrafficStats {
	tm.mu.RLock()
	defer tm.mu.RUnlock()

	result := make(map[string]*TrafficStats, len(tm.stats))
	for ip, stats := range tm.stats {
		var item = *stats
		result[ip] = &item
	}
	return result
}

// 重置统计数据
func (tm *TrafficManager) FlushStats() {
	tm.mu.Lock()
	defer tm.mu.Unlock()
	tm.stats = map[string]*TrafficStats{}
}

// 关闭流量管理器
func (tm *TrafficManager) Close() {
	// 停止计时器
	if tm.flushTimer != nil {
		tm.flushTimer.Stop()
	}

	// 发送停止信号
	close(tm.stopCh)

	// 等待处理协程完成
	tm.wg.Wait()

}

func (tm *TrafficManager) capture(ifaceName, syntax string) {
	var fanoutGroupID uint16 = 0x2021
	// 创建 TPacket 对象（参数可调节以适配性能/延迟）
	handle, err := afpacket.NewTPacket(
		afpacket.OptInterface(ifaceName),
		afpacket.OptBlockSize(1<<22), // 4MB
		afpacket.OptNumBlocks(64),    // 共 256MB
		afpacket.OptFrameSize(65536), // MTU 最大值
		afpacket.OptPollTimeout(afpacket.DefaultPollTimeout),
		afpacket.OptTPacketVersion(afpacket.TPacketVersion3),
	)
	if err != nil {
		fmt.Printf("failed to create handle: %v\n", err)
		return
	}
	defer handle.Close()
	err = handle.SetFanout(afpacket.FanoutCBPF, fanoutGroupID)
	if err != nil {
		fmt.Printf("failed to SetFanout: %v\n", err)
		return
	}
	// 设置 BPF 过滤器，添加主机过滤
	linkType := layers.LinkTypeEthernet // 一般为 Ethernet
	bpfIns, err := pcap.CompileBPFFilter(linkType, 65536, syntax)
	if err != nil {
		fmt.Printf("failed to compile BPF filter: %v\n", err)
		return
	}
	rawInstructions := []bpf.RawInstruction{}
	for _, v := range bpfIns {
		rawInstructions = append(rawInstructions, bpf.RawInstruction{
			Op: v.Code,
			Jt: v.Jt,
			Jf: v.Jf,
			K:  v.K,
		})
	}
	err = handle.SetBPF(rawInstructions)
	if err != nil {
		fmt.Printf("failed to apply BPF filter: %v\n", err)
		return
	}
	// 主循环
	for {
		select {
		case <-tm.stopCh:
			fmt.Println("context donw")
			return
		default:
			data, _, err := handle.ZeroCopyReadPacketData()
			if err == afpacket.ErrTimeout {
				// 超时继续
				fmt.Println("超时")
				continue
			}
			if err != nil {
				fmt.Println("抓包失败: " + err.Error())
				return
			}
			// 使用 gopacket 解析数据
			packet := gopacket.NewPacket(data, layers.LinkTypeEthernet, gopacket.Default)
			if ethernetLayer := packet.Layer(layers.LayerTypeEthernet); ethernetLayer != nil {
				ethernetPacket, _ := ethernetLayer.(*layers.Ethernet)
				if ethernetPacket.EthernetType == layers.EthernetTypeIPv4 {
					if ipLayer := packet.Layer(layers.LayerTypeIPv4); ipLayer != nil {
						// 转换为 IPv4 对象
						ip, _ := ipLayer.(*layers.IPv4)
						tm.updateStats(ip.SrcIP, ip.DstIP, uint32(len(packet.LinkLayer().LayerPayload())))
					}
				}
			}
		}
	}
}
