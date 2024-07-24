package observer

import "testing"

func TestRun(t *testing.T) {

	shirtItem := NewItem("Nike Shirt")

	observerFirst := &Customer{ID: "abc@gmail.com"}
	observerSecond := &Customer{ID: "xyz@gmail.com"}

	shirtItem.Register(observerFirst)
	shirtItem.Register(observerSecond)

	shirtItem.UpdateAvailability()
}
