package utils

import (
	"regexp"
	"strings"
)

// checkIfImageHasTag 判断 Docker 镜像地址是否带有标签
// 解析 URL 后，从路径部分提取标签
func HasImageTag(url string) bool {
	// 处理URL路径部分
	path := url
	if idx := strings.Index(url, "://"); idx != -1 {
		path = url[idx+3:]
	}
	parts := strings.SplitN(path, "/", 3)

	// 提取可能的镜像名称部分
	var imagePart string
	if len(parts) > 0 {
		imagePart = parts[len(parts)-1]
	}

	// 使用正则表达式判断是否包含标签
	re := regexp.MustCompile(`:[^/:]+$`)
	return re.MatchString(imagePart)
}
