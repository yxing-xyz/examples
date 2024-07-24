package visitor

import "fmt"

type MiddleCoordinates struct {
	X int
	Y int
}

func (m *MiddleCoordinates) VisitForSquare(s *Square) {
	// Calculate middle point coordinates for square.
	// Then assign in to the x and y instance variable.
	fmt.Println("Calculating middle point coordinates for square")
}

func (m *MiddleCoordinates) VisitForCircle(c *Circle) {
	fmt.Println("Calculating middle point coordinates for circle")
}

func (m *MiddleCoordinates) VisitForRectangle(r *Rectangle) {
	fmt.Println("Calculating middle point coordinates for rectangle")
}
