package bridge

import "fmt"

type Windows struct {
	Printer Printer
}

func (w *Windows) print() {
	fmt.Println("Print request for windowds")
	w.Printer.PrintFile()
}

func (w *Windows) SetPrinter(printer Printer) {
	w.Printer = printer
}
