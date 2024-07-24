package facade

import "fmt"

type Ledger struct {
}

func (s *Ledger) MakeEntry(accountID, txnType string, amount int) {
	fmt.Printf("Make leger entry for AccountID %s with txnType %s for amount %d\n", accountID, txnType, amount)
	return
}
