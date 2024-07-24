package main

import "sync"

type LinkStack struct {
	root *LinkNode
	size int
	lock sync.Mutex
}
type LinkNode struct {
	Next  *LinkNode
	Value int
}

func (l *LinkStack) Push(d int) {
	l.lock.Lock()
	defer l.lock.Unlock()
	newNode := new(LinkNode)
	newNode.Value = d
	if l.root != nil {
		preNode := l.root
		newNode.Next = preNode
	}
	l.root = newNode
	l.size++
}

func (l *LinkStack) Pop() (int, bool) {
	l.lock.Lock()
	defer l.lock.Unlock()
	if l.size == 0 {
		return 0, false
	}
	root := l.root
	d := root.Value

	l.root = root.Next
	l.size--
	return d, true
}
