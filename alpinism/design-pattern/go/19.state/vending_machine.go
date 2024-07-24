package state

import "fmt"

type VendingMachine struct {
	HasItem       IState
	ItemRequested IState
	HasMoney      IState
	Noitem        IState
	CurrentState  IState
	itemCount     int
	itemPrice     int
}

func NewVendingMachine(itemCount, itemPrice int) *VendingMachine {
	v := &VendingMachine{
		itemCount: itemCount,
		itemPrice: itemPrice,
	}
	hasItemState := &HasItemState{
		vendingMachine: v,
	}
	itemRequestedState := &ItemRequestedState{
		vendingMachine: v,
	}
	hasMoneyState := &HasMoneyState{
		vendingMachine: v,
	}
	noItemState := &NoItemState{
		vendingMachine: v,
	}
	v.SetState(hasItemState)
	v.HasItem = hasItemState
	v.ItemRequested = itemRequestedState
	v.HasMoney = hasMoneyState
	v.Noitem = noItemState
	return v
}

func (v *VendingMachine) AddItem(count int) error {
	return v.CurrentState.AddItem(count)
}

func (v *VendingMachine) RequestItem() error {
	return v.CurrentState.RequestItem()
}

func (v *VendingMachine) InsertMoney(money int) error {
	return v.CurrentState.InsertMoney(money)
}

func (v *VendingMachine) DispenseItem() error {
	return v.CurrentState.DispenseItem()
}

func (v *VendingMachine) SetState(s IState) {
	v.CurrentState = s
}

func (v *VendingMachine) IncrementItemCount(count int) {
	fmt.Printf("Adding %d items \n", count)
	v.itemCount += count
}
