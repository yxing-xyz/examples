package composite

import "fmt"

type Folder struct {
	Components []IComponent
	Name       string
}

func (f *Folder) Search(keyword string) {
	fmt.Printf("Searching recursively for keyword %s in folder %s\n", keyword, f.Name)
	for _, component := range f.Components {
		component.Search(keyword)
	}
}

func (f *Folder) Add(c IComponent) {
	f.Components = append(f.Components, c)
}
