package adapter

import "fmt"

type mac struct {
}

func (this *mac) insertIntoLightningPort() {
	fmt.Println("Lightning connector is plugged into mac machine.")
}
