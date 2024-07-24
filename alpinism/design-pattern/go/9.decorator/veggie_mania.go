package decorator

type veggMania struct{}

func (this *veggMania) getPrice() int {
	return 15
}
