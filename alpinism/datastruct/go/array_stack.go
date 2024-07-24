package main

import (
	"sync"
)

type ArrayStack struct {
	array []int
	size  int
	lock  sync.Mutex
}

func (a *ArrayStack) Push(d int) {
	a.lock.Lock()
	defer a.lock.Unlock()
	a.array = append(a.array, d)
	a.size++
}

func (a *ArrayStack) Pop() (int, bool) {
	a.lock.Lock()
	defer a.lock.Unlock()
	if a.size == 0 {
		return 0, false
	}

	d := a.array[a.size-1]
	// 这里可以优化, 如果记录一个slice底层最大长度, 和当前使用长度, 计算负载因子, 低于某个值, 缩容
	a.array = a.array[0 : a.size-1]
	a.size--
	return d, true
}
