package main

import (
	"sync"
)

type ArrayQueue struct {
	array []int
	size  int
	lock  sync.Mutex
}

func (a *ArrayQueue) Add(d int) {
	a.lock.Lock()
	defer a.lock.Unlock()
	a.array = append(a.array, d)
	a.size++
}

func (a *ArrayQueue) Remove() (int, bool) {
	a.lock.Lock()
	defer a.lock.Unlock()
	if a.size == 0 {
		return 0, false
	}

	d := a.array[0]
	// 底层持有的数组空间未释放, 这种存在浪费空间, 可以通过负载因子判断后迁移缩小容
	a.array = a.array[1:]
	a.size--
	return d, true
}
