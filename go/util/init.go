package util

import (
	"time"
)

func init() {
	// 设置东八区作为本地时区
	var cst, err = time.LoadLocation("Asia/Shanghai")
	time.Local = cst
	if err != nil {
		panic(err)
	}
}
