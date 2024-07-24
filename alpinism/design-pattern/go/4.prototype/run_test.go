package prototype

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	file1 := &File{
		Name: "File1",
	}
	file2 := &File{
		Name: "File2",
	}
	file3 := &File{
		Name: "File3",
	}
	folder1 := &Folder{
		Children: []INode{file1},
		Name:     "folder1",
	}
	folder2 := &Folder{
		Children: []INode{folder1, file2, file3},
		Name:     "folder2",
	}
	fmt.Println("\nPrinting hierarchy for Folder2")
	folder2.Print(" ")

	cloneFolder := folder2.Clone()
	fmt.Println("\nPrinting hierarchy for clone Folder")
	cloneFolder.Print("  ")
}
