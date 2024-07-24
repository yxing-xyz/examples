package memento

type Caretaker struct {
	MementoArray []*memento
}

func (c *Caretaker) AddMemento(m *memento) {
	c.MementoArray = append(c.MementoArray, m)
}

func (c *Caretaker) GetMemento(index int) *memento {
	return c.MementoArray[index]
}
