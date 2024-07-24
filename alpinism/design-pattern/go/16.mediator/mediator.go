package mediator

type IMediator interface {
	CanArrive(ITrain) bool
	NotifyAboutDeparture()
}
