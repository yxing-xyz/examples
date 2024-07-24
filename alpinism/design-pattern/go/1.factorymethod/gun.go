package factorymethod

type iGun interface {
	setName(name string)
	setPower(power int)
	getName() string
	getPower() int
}

type gun struct {
	name  string
	power int
}

func (r *gun) setName(name string) {
	r.name = name
}

func (r *gun) setPower(power int) {
	r.power = power
}

func (r gun) getName() string {
	return r.name
}

func (r gun) getPower() int {
	return r.power
}
