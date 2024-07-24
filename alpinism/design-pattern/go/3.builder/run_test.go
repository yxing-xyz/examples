package builder

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	normalBuilder, err := GetBuilder("normal")
	if err != nil {
		panic(err)
	}
	iglooBuilder, err := GetBuilder("igloo")
	if err != nil {
		panic(err)
	}
	direcotr := NewDirector(normalBuilder)
	normalHouse, err := direcotr.BuildHouse()
	if err != nil {
		panic(err)
	}

	fmt.Printf("Normal House Door Type: %s\n", normalHouse.DoorType)
	fmt.Printf("Normal House Window Type: %s\n", normalHouse.WindowType)
	fmt.Printf("Normal House Num Floor: %d\n", normalHouse.Floor)

	direcotr.SetBuilder(iglooBuilder)
	iglooHouse, err := direcotr.BuildHouse()
	if err != nil {
		panic(err)
	}
	fmt.Printf("\nIgloo House Door Type: %s\n", iglooHouse.DoorType)
	fmt.Printf("Igloo House Window Type: %s\n", iglooHouse.WindowType)
	fmt.Printf("Igloo House Num Floor: %d\n", iglooHouse.Floor)
}
