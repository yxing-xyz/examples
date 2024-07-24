package state

type IState interface {
	AddItem(int) error
	RequestItem() error
	InsertMoney(money int) error
	DispenseItem() error
}
