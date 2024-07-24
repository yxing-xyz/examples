package iterator

type UserIterator struct {
	Index int
	Users []*User
}

func (ui *UserIterator) hasNext() bool {
	return ui.Index < len(ui.Users)
}

func (ui *UserIterator) GetNext() *User {
	if ui.hasNext() {
		user := ui.Users[ui.Index]
		ui.Index++
		return user
	}
	return nil
}