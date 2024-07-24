package bridge

import "fmt"

type Hp struct{}

func (h *Hp) PrintFile() {
	fmt.Println("Printing by a HP Printer")
}
