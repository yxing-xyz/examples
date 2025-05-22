package utils

import (
	"archive/tar"
	"compress/gzip"
	"fmt"
	"io"
	"net/http"
	"os"
	"path"
	"path/filepath"
	"runtime"
	"strings"
)

// 下载重试
func DownloadWithRetry(url, filepath string) error {

	var fn = func() error {
		log.Printf("正在下载URL: ", url)
		resp, err := http.Get(url)
		if err != nil {
			log.Printf("failed to download url: %s, err: %v", url, err)
			return err
		}
		defer resp.Body.Close()

		if resp.StatusCode != http.StatusOK {
			log.Printf("错误的状态码,download url: %s", url)
			return fmt.Errorf("bad status: %s", resp.Status)
		}

		out, err := os.Create(filepath)
		if err != nil {
			log.Printf("创建文件,download url: %s, filepath: %s", url, filepath)
			return err
		}
		defer out.Close()

		_, err = io.Copy(out, resp.Body)
		if err != nil {
			log.Printf("写入文件失败, download url: %s, filepath: %s", url, filepath)
			return err
		}

		log.Printf("下载文件成功, download url: %s, filepath: %s", url, filepath)
		return nil
	}
	return DefaultRetryConfig.Apply(fn)
}

// DownloadAndExtractTarGzWithRetry 下载并解压 .tar.gz 文件，支持重试和 stripComponents
func DownloadAndExtractTarGzWithRetry(url, targetDir string, stripComponents int) error {

	fn := func() error {
		log.Printf("正在下载并解压: %s -> %s", url, targetDir)
		resp, err := http.Get(url)
		if err != nil {
			log.Printf("下载失败: %s, 错误: %v", url, err)
			return err
		}
		defer resp.Body.Close()

		if resp.StatusCode != http.StatusOK {
			log.Printf("HTTP 状态码错误: %d, URL: %s", resp.StatusCode, url)
			return fmt.Errorf("bad status: %s", resp.Status)
		}

		// 检查 body 是否为空
		if resp.ContentLength == 0 {
			log.Printf("响应内容为空: %s", url)
			return fmt.Errorf("empty response body")
		}

		gzr, err := gzip.NewReader(resp.Body)
		if err != nil {
			log.Printf("gzip 解压失败: %v", err)
			return err
		}
		defer gzr.Close()

		tarReader := tar.NewReader(gzr)

		for {
			header, err := tarReader.Next()
			if err == io.EOF {
				break
			}
			if err != nil {
				log.Printf("读取 tar 文件失败: %v", err)
				return err
			}

			// 构建目标路径，并处理 stripComponents
			relativePath := stripTarPath(header.Name, stripComponents)
			if relativePath == "" {
				continue // 被 strip 剥光了
			}
			targetPath := filepath.Join(targetDir, relativePath)
			// 安全性检查：防止路径穿越攻击
			absTargetDir, _ := filepath.Abs(targetDir)
			absFilePath, _ := filepath.Abs(targetPath)

			if !strings.HasPrefix(absFilePath, absTargetDir+string(os.PathSeparator)) && absFilePath != absTargetDir {
				log.Printf("路径穿越检测失败: %s", absFilePath)
				return fmt.Errorf("非法路径: %s", header.Name)
			}

			switch header.Typeflag {
			case tar.TypeDir:
				if err := os.MkdirAll(targetPath, os.FileMode(header.Mode).Perm()); err != nil {
					log.Printf("创建目录失败: %s, 错误: %v", targetPath, err)
					return err
				}
				if err := chownIfPossible(targetPath, header.Uid, header.Gid); err != nil {
					log.Printf("设置目录属主失败（忽略）: %s, 错误: %v", targetPath, err)
				}

			case tar.TypeReg:
				if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
					log.Printf("创建父目录失败: %s, 错误: %v", targetPath, err)
					return err
				}
				outFile, err := os.OpenFile(targetPath, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, os.FileMode(header.Mode).Perm())
				if err != nil {
					log.Printf("打开文件失败: %s, 错误: %v", targetPath, err)
					return err
				}
				if _, err := io.Copy(outFile, tarReader); err != nil {
					_ = outFile.Close()
					log.Printf("写入文件失败: %s, 错误: %v", targetPath, err)
					return err
				}
				_ = outFile.Close()
				if err := chownIfPossible(targetPath, header.Uid, header.Gid); err != nil {
					log.Printf("设置文件属主失败（忽略）: %s, 错误: %v", targetPath, err)
				}
			case tar.TypeSymlink:
				if err := os.MkdirAll(filepath.Dir(targetPath), 0755); err != nil {
					log.Printf("创建符号链接父目录失败: %s, 错误: %v", targetPath, err)
					return err
				}
				if err := os.Symlink(header.Linkname, targetPath); err != nil {
					log.Printf("创建符号链接失败: %s -> %s, 错误: %v", targetPath, header.Linkname, err)
					return err
				}
				log.Printf("创建符号链接: %s -> %s", targetPath, header.Linkname)
			default:
				log.Printf("忽略未知类型: %s", header.Name)
			}
		}
		log.Printf("下载并解压完成: %s -> %s", url, targetDir)
		return nil
	}
	return DefaultRetryConfig.Apply(fn)
}

func stripTarPath(p string, stripComponents int) string {
	if stripComponents <= 0 {
		return p
	}

	cleanPath := path.Clean(p) // 使用 UNIX 风格路径清洗
	segments := strings.Split(cleanPath, "/")

	if len(segments) <= stripComponents {
		return ""
	}
	return path.Join(segments[stripComponents:]...)
}

// chownIfPossible 尝试更改文件/目录的所有者（仅在非 Windows 平台有效）
func chownIfPossible(name string, uid, gid int) error {
	if runtime.GOOS == "windows" {
		return nil
	}
	return os.Chown(name, uid, gid)
}
