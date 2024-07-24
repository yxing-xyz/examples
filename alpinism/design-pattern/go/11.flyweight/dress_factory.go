package flyweight

import "fmt"

const (
	TerroristDressType        = "tDress"
	CounterTerroristDressType = "ctDress"
)

var dressFactorySingleInstance = &dressFactory{
	dressMap: make(map[string]IDress),
}

type dressFactory struct {
	dressMap map[string]IDress
}

func (d *dressFactory) GetDressByType(dressType string) (IDress, error) {
	if val, ok := d.dressMap[dressType]; ok {
		return val, nil
	}

	if dressType == TerroristDressType {
		d.dressMap[dressType] = NewTerroristDress()
		return d.dressMap[dressType], nil
	}
	if dressType == CounterTerroristDressType {
		d.dressMap[dressType] = NewCounterTerroristDress()
		return d.dressMap[dressType], nil
	}
	return nil, fmt.Errorf("Wrong dress type passed")
}

func (d *dressFactory) Print() {
	for dressType, dress := range d.dressMap {
		fmt.Printf("DressColorType: %s\nDressColor: %s\n", dressType, dress.GetColor())
	}
}

func GetDressSingleInstance() *dressFactory {
	return dressFactorySingleInstance
}
