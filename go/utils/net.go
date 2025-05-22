package utils

import (
	"fmt"
	"math/big"
	"net"
)

// 判断是否是内网IP
func IsInternalIP(ip net.IP) bool {
	if ip == nil {
		return false
	}

	// IPv4内网地址范围
	if ip4 := ip.To4(); ip4 != nil {
		return ip4[0] == 10 ||
			(ip4[0] == 172 && ip4[1] >= 16 && ip4[1] <= 31) ||
			(ip4[0] == 192 && ip4[1] == 168)
	}

	// IPv6链路本地地址
	if ip.IsLinkLocalUnicast() || ip.IsLinkLocalMulticast() {
		return true
	}

	return false
}

// 获取主机位的数量
func GetHostBitsCount(cidr string) (int, error) {
	// 解析CIDR地址
	_, ipnet, err := net.ParseCIDR(cidr)
	if err != nil {
		return 0, err
	}

	// 获取网络位的大小
	ones, _ := ipnet.Mask.Size() // ones 是网络部分的位数

	// 计算主机位的数量 = 总位数 32 - 网络位的数量
	hostBitsCount := 32 - ones
	return hostBitsCount, nil
}

// 计算主机可用的地址总数
func GetTotalHostAddresses(cidr string) (int, error) {
	hostBitsCount, err := GetHostBitsCount(cidr)
	if err != nil {
		return 0, err
	}

	// 计算总的主机地址数 = 2^主机位数
	totalHostAddresses := 1 << hostBitsCount

	// 减去网络地址和广播地址
	// 主机地址总数 - 2 （网络地址和广播地址）
	totalUsableAddresses := totalHostAddresses - 2

	return totalUsableAddresses, nil
}

// 获取第i个可用IP（0表示第一个可用IP）
func GetNthAvailableIP(cidr string, i int) (net.IP, error) {
	_, ipnet, err := net.ParseCIDR(cidr)
	if err != nil {
		return nil, err
	}

	// 获取网络位的大小
	ones, _ := ipnet.Mask.Size()

	// 计算主机位数
	hostBitsCount := 32 - ones

	// 计算网络地址
	networkIP := ipnet.IP

	// 将网络地址转换为整数
	ipInt := big.NewInt(0)
	ipInt.SetBytes(networkIP)

	// 跳过网络地址，开始从 ipInt + 1
	ipInt.Add(ipInt, big.NewInt(1)) // 跳过网络地址

	// 计算广播地址：网络地址 + 2^主机位数 - 1
	broadcastIP := big.NewInt(0)
	broadcastIP.SetBytes(networkIP)
	broadcastIP.Add(broadcastIP, big.NewInt(1<<hostBitsCount)) // 广播地址：网络地址 + 2^主机位数

	// 计算总的可用地址数
	totalUsableAddresses := (1 << hostBitsCount) - 2 // 排除网络地址和广播地址

	// 检查 i 是否在合理范围内
	if i < 0 || i >= totalUsableAddresses {
		return nil, fmt.Errorf("out of range: no such IP exists")
	}

	// 增加偏移量 i，跳过网络地址
	ipInt.Add(ipInt, big.NewInt(int64(i)))

	// 确保返回的 IP 不等于广播地址
	if ipInt.Cmp(broadcastIP) >= 0 {
		return nil, fmt.Errorf("out of range: no such IP exists")
	}

	// 返回第 i 个可用 IP 地址
	ipBytes := ipInt.Bytes()

	// 创建并返回 net.IP 类型的地址
	// 需要补充长度，以确保它的长度为 4 字节
	if len(ipBytes) < 4 {
		ipBytes = append(make([]byte, 4-len(ipBytes)), ipBytes...)
	}
	ip := net.IP(ipBytes)

	return ip, nil
}
