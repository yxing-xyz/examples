package main

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

/*
                   1
				2     3
              4  5

// PreOrder: 1, 2, 4, 5, 3
// MidOrder: 4, 2, 5, 1, 3
// PostOrder: 4, 5, 2, 3, 3

*/
