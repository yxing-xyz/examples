package facade

import (
	"fmt"
	"log"
	"testing"
)

func TestRun(t *testing.T) {
	fmt.Println()
	walletFacade := NewWalletFacade("abc", 1234)
	fmt.Println()
	err := walletFacade.AddMontyToWallet("abc", 1234, 10)
	if err != nil {
		log.Fatalf("Error: %s\n", err.Error())
	}
	fmt.Println()
	err = walletFacade.DeductMoentyFromWallet("abc", 1234, 5)
	if err != nil {
		log.Fatalf("Error: %s\n", err.Error())
	}
}
