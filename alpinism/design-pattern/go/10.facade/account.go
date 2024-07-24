package facade

import "fmt"

type Account struct {
	Name string
}

func NewAccount(accoutName string) *Account {
	return &Account{
		Name: accoutName,
	}
}

func (a *Account) CheckAccount(accoutName string) error {
	if a.Name != accoutName {
		return fmt.Errorf("Account Name is incorrect")
	}
	fmt.Println("Account Verified")
	return nil
}
