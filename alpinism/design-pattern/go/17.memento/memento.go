package memento

type memento struct {
	state string
}

func (m *memento) GetSaveState() string {
	return m.state
}
