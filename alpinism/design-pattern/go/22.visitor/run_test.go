package visitor

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	square := &Square{Side: 2}
	circle := &Circle{Radius: 3}
	rectangle := &Rectangle{L: 2, B: 3}

	areaCalculator := &AreaCalculator{}

	square.Accept(areaCalculator)
	circle.Accept(areaCalculator)
	rectangle.Accept(areaCalculator)

	fmt.Println()
	middleCoordinates := &MiddleCoordinates{}
	square.Accept(middleCoordinates)
	circle.Accept(middleCoordinates)
	rectangle.Accept(middleCoordinates)
}
