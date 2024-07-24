package abstractfactory

type iShirt interface {
	setLogo(logo string)
	setSize(size int)
	getLogo() string
	getSize() int
}

type shirt struct {
	logo string
	size int
}

func (this *shirt) setLogo(logo string) {
	this.logo = logo
}

func (this *shirt) setSize(size int) {
	this.size = size
}

func (this *shirt) getLogo() string {
	return this.logo
}
func (this *shirt) getSize() int {
	return this.size
}
