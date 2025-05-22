package utils

import (
	"fmt"
	"os"
	"path/filepath"
	"syscall"
)

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

func RemovePath(path string) error {
	info, err := os.Lstat(path)
	if err != nil {
		if os.IsNotExist(err) {
			// 不存在则不报错
			return nil
		}
		return fmt.Errorf("无法读取路径信息: %w", err)
	}

	// 是目录则递归删除
	if info.IsDir() {
		err = os.RemoveAll(path)
		if err != nil {
			return fmt.Errorf("删除目录失败: %w", err)
		}
	} else {
		err = os.Remove(path)
		if err != nil {
			return fmt.Errorf("删除文件失败: %w", err)
		}
	}
	return nil
}

// 获取目录空间的总大小
func DirSize(dir string) (int64, error) {
	var totalSize int64

	// 使用 filepath.Walk 函数递归遍历目录
	err := filepath.Walk(dir, func(path string, info os.FileInfo, err error) error {
		if err != nil {
			// 如果遇到错误，返回
			return err
		}

		// 累加目录和文件的大小
		// 这里我们认为目录本身也有空间消耗，info.Size() 会返回目录元数据的大小
		totalSize += info.Size()

		return nil
	})

	if err != nil {
		return 0, err
	}

	return totalSize, nil
}

// 追加文件
func AppendFile(name string, data []byte, perm os.FileMode) error {
	f, err := os.OpenFile(name, os.O_WRONLY|os.O_CREATE|os.O_APPEND, perm)
	if err != nil {
		return err
	}
	_, err = f.Write(data)
	if err1 := f.Close(); err1 != nil && err == nil {
		err = err1
	}
	return err
}
