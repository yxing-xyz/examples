package state

import "fmt"

type HasItemState struct {
	vendingMachine *VendingMachine
}

func (i *HasItemState) AddItem(count int) error {
	fmt.Printf("%d items added\n", count)
	i.vendingMachine.IncrementItemCount(count)
	return nil
}

func (i *HasItemState) RequestItem() error {
	if i.vendingMachine.itemCount == 0 {
		i.vendingMachine.SetState(i.vendingMachine.Noitem)
		return fmt.Errorf("no item present")
	}
	fmt.Printf("item requestd\n")
	i.vendingMachine.SetState(i.vendingMachine.ItemRequested)
	return nil
}

func (i *HasItemState) InsertMoney(money int) error {
	return fmt.Errorf("please select item first")
}

func (i *HasItemState) DispenseItem() error {
	return fmt.Errorf("please select item first")
}
