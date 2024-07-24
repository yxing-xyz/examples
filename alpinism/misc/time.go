package misc

// t 时间戳
// 将时间戳转为北京时间去除小时分秒
func FloorInCST(t int64) int64 {
	return t - (t+8*3600)%86400
}
