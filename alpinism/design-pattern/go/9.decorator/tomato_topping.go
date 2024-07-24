package decorator

type tomatoTopping struct {
	pizza pizza
}

func (this *tomatoTopping) getPrice() int {
	pizzaPrice := this.pizza.getPrice()
	return pizzaPrice + 7
}
