package observer

// 主体
type ISubject interface {
	Register(obs IObserver)   //TODO
	Deregister(obs IObserver) //TODO
	NotifyAll()               //TODO
}
