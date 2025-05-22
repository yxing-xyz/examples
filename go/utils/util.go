package utils

import (
	"crypto/md5"
	"fmt"
	"io"
	"net"
	"os"
	"reflect"
	"strconv"
	"strings"

	"github.com/pkg/errors"
	"github.com/shirou/gopsutil/disk"
)

/*
 *  取结构体字段名
 */
func FieldName(in interface{}) string {
	t := reflect.TypeOf(in)
	if t.Kind() != reflect.Struct {
		panic(fmt.Errorf("var is not struct"))
	}
	v := reflect.ValueOf(in)
	for i := 0; i < t.NumField(); i++ {
		fieldT := t.Field(i)
		fieldV := v.FieldByName(fieldT.Name)
		// 嵌套结构体递归比较
		if fieldT.Type.Kind() == reflect.Struct {
			return FieldName(fieldV.Interface())
		}
		if !fieldV.IsZero() {
			return fieldT.Name
		}
	}
	panic(fmt.Errorf("all field is zero"))
}

// LittleEndianLong2IP 主机字节序(小端序)long转点分ip
func LittleEndianLong2IP(ipv4 uint32) string {
	return net.IPv4(byte(ipv4>>24), byte(ipv4>>16), byte(ipv4>>8), byte(ipv4)).String()
}

// BigEndianLong2IP 网络字节序(大端序)转点分ip
func BigEndianLong2IP(ipv4 uint32) string {
	return net.IPv4(byte(ipv4), byte(ipv4>>8), byte(ipv4>>16), byte(ipv4>>24)).String()
}

func IP2Long(ipv4 string) (uint32, error) {
	ipv4List := strings.Split(ipv4, ".")
	if len(ipv4List) != 4 {
		return 0, fmt.Errorf("parameter non IPV4 format: %s", ipv4)
	}
	var ip uint64
	for k := range ipv4List {
		partOfIp, err := strconv.ParseUint(ipv4List[len(ipv4List)-k-1], 10, 64)
		if partOfIp > 255 {
			return 0, fmt.Errorf("exceeding the maximum range of IPv4: %s", ipv4)
		}
		if err != nil {
			return 0, err
		}
		ip |= partOfIp << (8 * k)
	}
	return uint32(ip), nil
}

// 检查是否是容器内部
func InContainer() (bool, error) {
	pstats, err := disk.Partitions(true)
	if err != nil {
		return false, errors.Wrap(err, "get disk info failed")
	}
	for _, value := range pstats {
		if value.Mountpoint == "/" && strings.EqualFold("overlay", value.Fstype) {
			return true, nil
		}
	}

	return false, nil

}

// FileMD5 返回指定文件的MD5哈希值
func FileMD5(filePath string) (string, error) {
	// 打开文件
	file, err := os.Open(filePath)
	if err != nil {
		return "", fmt.Errorf("failed to open file: %w", err)
	}
	defer file.Close()

	// 创建MD5哈希器
	hasher := md5.New()

	// 使用io.Copy将文件内容复制到哈希器
	_, err = io.Copy(hasher, file)
	if err != nil {
		return "", fmt.Errorf("failed to read file: %w", err)
	}

	// 获取哈希值
	digest := hasher.Sum(nil)

	// 将哈希值转换为16进制字符串
	MD5String := fmt.Sprintf("%x", digest)

	return MD5String, nil
}

func IsRegularFile(filePath string) (bool, error) {
	// 使用os.Stat获取文件信息
	info, err := os.Stat(filePath)
	if err != nil {
		if os.IsNotExist(err) {
			return false, nil
		} else {
			return false, err
		}
	}
	if !info.Mode().IsRegular() {
		return false, fmt.Errorf("%s is directory", filePath)
	}
	return true, nil
}
