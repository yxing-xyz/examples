package bridge

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	hpPrinter := &Hp{}
	epsonPrinter := &Epson{}

	macComputer := &Mac{}
	macComputer.SetPrinter(hpPrinter)
	macComputer.print()
	fmt.Println()

	macComputer.SetPrinter(epsonPrinter)
	macComputer.print()
	fmt.Println()

	windowsComputer := &Windows{}
	windowsComputer.SetPrinter(hpPrinter)
	windowsComputer.print()
	fmt.Println()

	windowsComputer.SetPrinter(epsonPrinter)
	windowsComputer.print()

}
