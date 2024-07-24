package decorator

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	pizza := &veggMania{}

	pizzaWithCheese := &cheeseTopping{pizza: pizza}
	pizzatWithCheeseAndTomato := &tomatoTopping{
		pizza: pizzaWithCheese,
	}

	fmt.Printf("price %d\n", pizzatWithCheeseAndTomato.getPrice())
}
