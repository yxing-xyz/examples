package mediator

import "testing"

func TestRun(t *testing.T) {
	stationManager := NewStationManger()

	passengerTrain := &PassengerTrain{
		mediator: stationManager,
	}
	freightTrain := &FreightTrain{
		mediator: stationManager,
	}

	passengerTrain.Arrive()
	freightTrain.Arrive()
	passengerTrain.Depart()
}
