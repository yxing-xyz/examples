package abstractfactory

type nickFactory struct {
}

func (this *nickFactory) makeShoe() iShoe {
	return &nickShoe{
		shoe{
			logo: "nick",
			size: 40,
		},
	}
}

func (this *nickFactory) makeShirt() iShirt {
	return &nickShirt{
		shirt{
			logo: "nick",
			size: 20,
		},
	}
}
