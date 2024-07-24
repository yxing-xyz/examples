package main

import "fmt"

type BinaryTreeNode struct {
	Data  int
	Left  *BinaryTreeNode
	Right *BinaryTreeNode
}

func NewBinaryTreeNode(data int) *BinaryTreeNode {
	return &BinaryTreeNode{
		Data: data,
	}
}

func (root *BinaryTreeNode) GetTreeNodeNum() int {
	if root == nil {
		return 0
	}
	// 左字树计算 + 右子数计算 + 1(本身这个节点)
	return root.Left.GetTreeNodeNum() + root.Right.GetTreeNodeNum() + 1
}

func (root *BinaryTreeNode) GetTreeDegree() int {
	maxDeggree := 0
	if root == nil {
		return maxDeggree
	}

	leftDegree := root.Left.GetTreeDegree()
	rightDegree := root.Right.GetTreeDegree()
	if leftDegree > rightDegree {
		maxDeggree = leftDegree
	} else {
		maxDeggree = rightDegree
	}
	return leftDegree + 1
}

func (root *BinaryTreeNode) PreOrder() {
	if root != nil {
		fmt.Printf("%d  ", root.Data)
		root.Left.PreOrder()
		root.Right.PreOrder()
	}
}

func (root *BinaryTreeNode) MidOrder() {
	if root != nil {
		root.Left.MidOrder()
		fmt.Printf("%d ", root.Data)
		root.Right.MidOrder()
	}
}

func (root *BinaryTreeNode) PostOrder() {
	if root != nil {
		root.Left.PostOrder()
		root.Right.PostOrder()
		fmt.Printf("%d ", root.Data)
	}
}

/*
func main() {
	node1 := NewBinaryTreeNode(1)
	node2 := NewBinaryTreeNode(2)
	node3 := NewBinaryTreeNode(3)
	node4 := NewBinaryTreeNode(4)
	node5 := NewBinaryTreeNode(5)
	node1.Left = node2
	node1.Right = node3
	node2.Left = node4
	node2.Right = node5

	node1.PostOrder()
}


//                 1
//				2     3
//            4  5

// PreOrder: 1, 2, 4, 5, 3
// MidOrder: 4, 2, 5, 1, 3
// PostOrder: 4, 5, 2, 3, 3
*/
