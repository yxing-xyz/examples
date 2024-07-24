package chain_of_responsibility

import "fmt"

type Cashier struct {
	next IDepartMent
}

func (c *Cashier) Execute(p *Patient) {
	if p.PaymentDone {
		fmt.Println("Payment done")
	}
	fmt.Println("Cashier getting money from patient")
}

func (c *Cashier) SetNext(next IDepartMent) {
	c.next = next
}
