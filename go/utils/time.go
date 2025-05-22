package utils

import (
	"fmt"
	"math"
	"time"

	"github.com/beevik/ntp"
	"golang.org/x/sys/unix"
)

// 设置系统时间

func SetSystemTime(ntpTime time.Time) error {
	ts := unix.NsecToTimespec(ntpTime.UnixNano())
	err := unix.ClockSettime(unix.CLOCK_REALTIME, &ts)
	if err != nil {
		return fmt.Errorf("failed to set system time: %v", err)
	}
	return nil
}
func SyncSystemTimeWithNTP(ntpServer string) bool {
	// 选择一个NTP服务器，这里使用pool.ntp.org作为示例
	// 向NTP服务器发起请求，获取时间信息
	ntpTime, err := ntp.Time(ntpServer)
	if err != nil {
		log.Printf("获取时间信息失败: %v", err)
		return false
	}
	localTime := time.Now()
	log.Printf("当前系统时间: %v, NTP服务器时间: %v", localTime, ntpTime)
	// 计算时间差
	diff := ntpTime.Sub(localTime)
	if math.Abs(float64(diff)) < float64(time.Second)*3 {
		// 误差小于3s不处理, 认为更新成功
		return true
	}
	err = SetSystemTime(ntpTime)
	if err != nil {
		log.Printf("设置系统时间失败: %v", err)
		return false
	}
	log.Printf("设置系统时间成功")
	return true
}
