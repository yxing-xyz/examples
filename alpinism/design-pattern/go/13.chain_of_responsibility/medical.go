package chain_of_responsibility

import "fmt"

type Medical struct {
	next IDepartMent
}

func (m *Medical) Execute(p *Patient) {
	if p.MedicineDone {
		fmt.Println("Medicine already given to patient")
		m.next.Execute(p)
		return
	}
	fmt.Println("Medical giving medicine to patient")
	p.MedicineDone = true
	m.next.Execute(p)
}

func (m *Medical) SetNext(next IDepartMent) {
	m.next = next
}