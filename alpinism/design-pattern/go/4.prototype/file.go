package prototype

import "fmt"

type File struct {
	Name string
}

func (f *File) Print(indentation string) {
	fmt.Println(indentation + f.Name)
}

func (f *File) Clone() INode {
	return &File{Name: f.Name + "_clone"}
}
