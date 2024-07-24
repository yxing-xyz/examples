package abstractfactory

type adiasFactory struct{}

func (this *adiasFactory) makeShoe() iShoe {
	return &adidasShoe{
		shoe{logo: "adidas", size: 40},
	}
}

func (this *adiasFactory) makeShirt() iShirt {
	return &adidasShirt{
		shirt{logo: "adidas", size: 20},
	}
}
