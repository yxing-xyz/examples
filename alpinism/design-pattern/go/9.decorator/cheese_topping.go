package decorator

type cheeseTopping struct {
	pizza pizza
}

func (this *cheeseTopping) getPrice() int {
	pizzaPrice := this.pizza.getPrice()
	return pizzaPrice + 10
}
