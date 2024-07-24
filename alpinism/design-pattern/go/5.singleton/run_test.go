package singleton

import (
	"fmt"
	"testing"
)

func TestRun(t *testing.T) {
	for i := 0; i < 30; i++ {
		go GetEarth()
	}
	fmt.Scanln()
}
