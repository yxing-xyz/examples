package main

import "sync"

type LinkQueue struct {
	tail *LinkNode //尾部节点, 尾部节点的next指向头部, 循环链表
	size int
	lock sync.Mutex
}

func NewLinkQueue() *LinkQueue {
	return &LinkQueue{
		tail: &LinkNode{},
	}
}

func (l *LinkQueue) Add(d int) {
	l.lock.Lock()
	defer l.lock.Unlock()
	node := new(LinkNode)
	node.Value = d
	// 保证只有一个元素的时候, 队头指向自己
	node.Next = node
	if l.size != 0 {
		head := l.tail.Next
		// 链上尾部
		l.tail.Next = node
		// 尾部链接头部
		node.Next = head
	}
	l.tail = node
	l.size++
	return
}

func (l *LinkQueue) Remove() (int, bool) {
	l.lock.Lock()
	defer l.lock.Unlock()

	if l.size == 0 {
		return 0, false
	}

	head := l.tail.Next
	// 指向队头后一个节点
	l.tail.Next = head.Next
	l.size--
	return head.Value, true
}
