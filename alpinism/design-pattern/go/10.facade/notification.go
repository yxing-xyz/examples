package facade

import "fmt"

type Notification struct {
}

func (n *Notification) SendWalletCrediNotification() {
	fmt.Println("Sending wallet credit notification")
}

func (n *Notification) SendWalletDebitNotification() {
	fmt.Println("Sending wallet debit notification")
}
