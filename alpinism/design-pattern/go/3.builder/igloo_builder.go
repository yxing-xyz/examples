package builder

type IglooBuilder struct {
	windowType string
	doorType   string
	floor      int
}

func NewIgLooBuilder() *IglooBuilder {
	return &IglooBuilder{}
}

func (b *IglooBuilder) SetWindowType() {
	b.windowType = "Snow Window"
}
func (b *IglooBuilder) SetDoorType() {
	b.doorType = "Snow Door"
}
func (b *IglooBuilder) SetNumFloor() {
	b.floor = 1
}
func (b *IglooBuilder) GetHouse() *House {
	return &House{
		WindowType: b.windowType,
		DoorType:   b.doorType,
		Floor:      b.floor,
	}
}
