package chain_of_responsibility

import "fmt"

type Doctor struct {
	next IDepartMent
}

func (d *Doctor) Execute(p *Patient) {
	if p.DoctorCheckUpDone {
		fmt.Println("Doctor checkup already done")
		d.next.Execute(p)
	}
	fmt.Println("Doctor checking patient")
	p.DoctorCheckUpDone = true
	d.next.Execute(p)
}

func (d *Doctor) SetNext(next IDepartMent) {
	d.next = next
}
