package observer

// 观察者
type IObserver interface {
	Update(string)
	GetID() string
}
