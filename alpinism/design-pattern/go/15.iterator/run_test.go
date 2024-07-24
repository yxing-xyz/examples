package iterator

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	user1 := &User{
		Name: "a",
		Age:  30,
	}
	user2 := &User{
		Name: "b",
		Age:  20,
	}
	UserCollection := &UserCollection{
		Users: []*User{user1, user2},
	}
	iterator := UserCollection.CreateIterator()
	for iterator.hasNext() {
		user := iterator.GetNext()
		fmt.Printf("User is %+v\n", user)
	}
}
