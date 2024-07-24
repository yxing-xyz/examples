package mediator

import "fmt"

type FreightTrain struct {
	mediator IMediator
}

func (f *FreightTrain) Arrive() {
	if !f.mediator.CanArrive(f) {
		fmt.Println("FreightTrain: Arrival blocked, waiting")
		return
	}
	fmt.Println("FreightTrain: Arrived")
}

func (f *FreightTrain) Depart() {
	fmt.Println("FreightTrain: Leaving")
	f.mediator.NotifyAboutDeparture()
}

func (f *FreightTrain) PermitArrival() {
	fmt.Println("FreightTrain: Arrival permitted")
	f.Arrive()
}
