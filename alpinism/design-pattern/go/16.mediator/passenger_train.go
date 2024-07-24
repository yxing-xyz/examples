package mediator

import "fmt"

type PassengerTrain struct {
	mediator IMediator
}

func (p *PassengerTrain) Arrive() {
	if !p.mediator.CanArrive(p) {
		fmt.Println("PassengerTrain: Arrival blocked, waiting")
		return
	}
	fmt.Println("PassengerTrain: Arrived")
}

func (p *PassengerTrain) Depart() {
	fmt.Println("PassengerTrain: Leaving")
	p.mediator.NotifyAboutDeparture()
}

func (p *PassengerTrain) PermitArrival() {
	fmt.Println("PassengerTrain: Arrival permitted, arriving")
	p.Arrive()
}
