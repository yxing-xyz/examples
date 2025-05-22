package utils

import "syscall"

type MountPointStat struct {
	CapacityBytes  uint64
	AvailableBytes uint64
	UsedBytes      uint64
}

// 挂载点信息
func GetMountPointStat(mountPoint string) (*MountPointStat, error) {
	var stat syscall.Statfs_t
	err := syscall.Statfs(mountPoint, &stat)
	if err != nil {
		return nil, err
	}
	return &MountPointStat{
		CapacityBytes:  uint64(stat.Blocks) * uint64(stat.Bsize),
		AvailableBytes: uint64(stat.Bavail) * uint64(stat.Bsize),
		UsedBytes:      uint64(stat.Blocks-stat.Bfree) * uint64(stat.Bsize),
	}, nil
}
