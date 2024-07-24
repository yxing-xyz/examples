package state

import "fmt"

type HasMoneyState struct {
	vendingMachine *VendingMachine
}

func (i *HasMoneyState) RequestItem() error {
	return fmt.Errorf("item dispense in progress")
}

func (i *HasMoneyState) AddItem(_ int) error {
	return fmt.Errorf("item dispense inprogress")
}

func (i *HasMoneyState) InsertMoney(money int) error {
	return fmt.Errorf("item out of stock")
}

func (i *HasMoneyState) DispenseItem() error {
	fmt.Println("dispensing item")
	i.vendingMachine.itemCount = i.vendingMachine.itemCount - 1
	if i.vendingMachine.itemCount == 0 {
		i.vendingMachine.SetState(i.vendingMachine.Noitem)
	} else {
		i.vendingMachine.SetState(i.vendingMachine.HasItem)
	}
	return nil
}
