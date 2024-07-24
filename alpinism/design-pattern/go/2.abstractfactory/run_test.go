package abstractfactory

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	adidasFactory, err := getSportsFactory("adidas")
	if err != nil {
		t.Fail()
	}
	nickFactory, err := getSportsFactory("nick")
	if err != nil {
		t.Fail()
	}
	nickShoe := nickFactory.makeShoe()
	nickShirt := nickFactory.makeShirt()
	adidasShoe := adidasFactory.makeShoe()
	adidasShirt := adidasFactory.makeShirt()
	printShirtDetails(nickShirt)
	printShirtDetails(adidasShirt)
	printShoeDetails(nickShoe)
	printShoeDetails(adidasShoe)

}

func printShoeDetails(s iShoe) {
	fmt.Printf("Logo: %s", s.getLogo())
	fmt.Println()
	fmt.Printf("Size: %d", s.getSize())
	fmt.Println()
}

func printShirtDetails(s iShirt) {
	fmt.Printf("Logo: %s", s.getLogo())
	fmt.Println()
	fmt.Printf("Size: %d", s.getSize())
	fmt.Println()
}
