package utils

import "math"

// 四舍五入函数
func RoundToDecimal(value float64, decimalPlaces int) float64 {
	shift := math.Pow(10, float64(decimalPlaces))
	return math.Round(value*shift) / shift
}
