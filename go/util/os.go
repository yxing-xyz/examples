package util

import (
	"fmt"
	"io"
	"os"
)

func MoveFile(sourcePath, destPath string) error {
	// 首先尝试直接使用os.Rename
	err := os.Rename(sourcePath, destPath)
	if err == nil {
		return nil // 移动成功
	}

	// 如果os.Rename失败，可能是跨文件系统，尝试使用CopyFile
	if _, ok := err.(*os.LinkError); ok {
		// 复制文件
		if err := CopyFile(destPath, sourcePath); err != nil {
			return fmt.Errorf("failed to copy file: %v", err)
		}

		// 删除源文件
		if err := os.Remove(sourcePath); err != nil {
			return fmt.Errorf("failed to delete the source file: %v", err)
		}
	} else {
		return fmt.Errorf("failed to move file: %v", err)
	}

	return nil // 移动成功
}

// CopyFile 函数模拟了Unix的cp -p命令，保留文件权限
func CopyFile(dstName, srcName string) error {
	src, err := os.Open(srcName)
	if err != nil {
		return err
	}
	defer src.Close()

	dst, err := os.Create(dstName)
	if err != nil {
		return err
	}
	defer dst.Close()

	// 保留源文件的权限
	si, err := os.Stat(srcName)
	if err != nil {
		return err
	}
	err = os.Chmod(dstName, si.Mode())
	if err != nil {
		return err
	}

	// 复制文件内容
	_, err = io.Copy(dst, src)
	if err != nil {
		return err
	}

	// 设置修改时间
	err = os.Chtimes(dstName, si.ModTime(), si.ModTime())
	if err != nil {
		return err
	}

	return nil
}
