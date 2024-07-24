package memento

type Originator struct {
	state string
}

func (e *Originator) CreateMemento() *memento {
	return &memento{state: e.state}
}

func (e *Originator) RestoreMemento(m *memento) {
	e.state = m.GetSaveState()
}

func (e *Originator) SetState(state string) {
	e.state = state
}

func (e *Originator) GetState() string {
	return e.state
}
