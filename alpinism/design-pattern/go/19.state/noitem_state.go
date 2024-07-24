package state

import "fmt"

type NoItemState struct {
	vendingMachine *VendingMachine
}

func (i *NoItemState) AddItem(count int) error {
	i.vendingMachine.IncrementItemCount(count)
	i.vendingMachine.SetState(i.vendingMachine.HasItem)
	return nil
}

func (i *NoItemState) RequestItem() error {
	return fmt.Errorf("item out of stock")
}

func (i *NoItemState) InsertMoney(money int) error {
	return fmt.Errorf("item out of stock")
}

func (i *NoItemState) DispenseItem() error {
	return fmt.Errorf("item out of stock")
}
