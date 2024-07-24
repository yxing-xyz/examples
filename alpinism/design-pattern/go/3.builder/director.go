package builder

import "errors"

type Director struct {
	builder IBuilder
}

func NewDirector(b IBuilder) *Director {
	return &Director{
		builder: b,
	}
}

func (d *Director) SetBuilder(b IBuilder) {
	d.builder = b
}

func (d *Director) BuildHouse() (*House, error) {
	if d.builder == nil {
		return nil, errors.New("builder can't empty")
	}
	d.builder.SetDoorType()
	d.builder.SetWindowType()
	d.builder.SetNumFloor()
	return d.builder.GetHouse(), nil
}
