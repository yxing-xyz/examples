package bridge

import "fmt"

type Mac struct {
	Printer Printer
}

func (mac *Mac) print() {
	fmt.Println("Print request for mac")
	mac.Printer.PrintFile()
}

func (mac *Mac) SetPrinter(printer Printer) {
	mac.Printer = printer
}
