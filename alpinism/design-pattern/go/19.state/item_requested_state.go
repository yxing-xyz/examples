package state

import "fmt"

type ItemRequestedState struct {
	vendingMachine *VendingMachine
}

func (i *ItemRequestedState) AddItem(_ int) error {
	return fmt.Errorf("item dispense inprogress")
}

func (i *ItemRequestedState) RequestItem() error {
	return fmt.Errorf("itme already requested")
}

func (i *ItemRequestedState) InsertMoney(money int) error {
	if money < i.vendingMachine.itemPrice {
		return fmt.Errorf("inserted money is less. please insert %d", i.vendingMachine.itemPrice)
	}
	fmt.Println("money entered is ok")
	i.vendingMachine.SetState(i.vendingMachine.HasMoney)
	return nil
}

func (i *ItemRequestedState) DispenseItem() error {
	return fmt.Errorf("please insert money first")
}
