package observer

import "fmt"

// 具体观察者

type Customer struct {
	ID string
}

func (c *Customer) Update(itemName string) {
	fmt.Printf("Sending email to customer %s for item %s\n", c.ID, itemName)
}

func (c *Customer) GetID() string {
	return c.ID
}
