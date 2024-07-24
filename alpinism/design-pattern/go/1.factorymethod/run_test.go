package factorymethod

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	ak47, err := getGun("ak47")
	if err != nil {
		panic(err)
	}
	masket, err := getGun("musket")
	if err != nil {
		panic(err)
	}

	printDetails(ak47)
	printDetails(masket)
}

func printDetails(g iGun) {
	fmt.Printf("Guns: %s", g.getName())
	fmt.Println()
	fmt.Printf("Power: %d", g.getPower())
	fmt.Println()
}
