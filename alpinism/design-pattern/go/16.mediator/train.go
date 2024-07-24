package mediator

type ITrain interface {
	Arrive()
	Depart()
	PermitArrival()
}
