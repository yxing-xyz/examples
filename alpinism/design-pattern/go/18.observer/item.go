package observer

import "fmt"

// 具体主体
type Item struct {
	ObserverList []IObserver
	Name         string
	InStock      bool
}

func NewItem(name string) *Item {
	return &Item{
		Name: name,
	}
}

func (i *Item) UpdateAvailability() {
	fmt.Printf("Item %s is now in stock \n", i.Name)
	i.InStock = true
	i.NotifyAll()
}

func (i *Item) Register(obs IObserver) {
	i.ObserverList = append(i.ObserverList, obs)
}

func (i *Item) Deregister(obs IObserver) {
	var index = -1
	for i, observer := range i.ObserverList {
		if obs.GetID() == observer.GetID() {
			index = i
			break
		}
	}
	if index != -1 {
		i.ObserverList = append(i.ObserverList[:index], i.ObserverList[index+1:]...)
	}
}

func (i *Item) NotifyAll() {
	for _, observer := range i.ObserverList {
		observer.Update(i.Name)
	}
}