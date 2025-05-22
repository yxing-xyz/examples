package utils

import "time"

type Logger interface {
	// Printf must have the same semantics as log.Printf.
	Printf(format string, args ...any)
}

var log Logger

func Init(l Logger) {
	log = l
}

func init() {
	// 设置东八区作为本地时区
	var cst, err = time.LoadLocation("Asia/Shanghai")
	time.Local = cst
	if err != nil {
		panic(err)
	}
}
