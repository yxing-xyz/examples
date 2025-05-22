package utils

import "math"

// 保留小数
func RoundToDecimal(value float64, decimalPlaces int) float64 {
	shift := math.Pow(10, float64(decimalPlaces))
	return math.Round(value*shift) / shift
}

// 以分为单位的数值转换为以元为单位并进行四舍五入的功能。
func CentsToRoundedYuan(cent int) int64 {
	return int64(math.Floor(float64(cent)/100 + 0.5))
}
