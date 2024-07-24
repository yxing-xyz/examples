package singleton

import (
	"fmt"
	"math"
	"sync"
)

type earth struct {
	Name   string
	Radius float64 // km
	Weight float64 // kg
}

var once sync.Once

var earthInstance *earth

func GetEarth() *earth {
	if earthInstance == nil {
		once.Do(func() {
			fmt.Println("创建地球")
			earthInstance = &earth{
				Name:   "地球",
				Radius: 6371 * 1000,
				Weight: 5.965 * math.Pow10(24),
			}
		})
	}
	fmt.Println("地球已经创建了，直接返回地球")
	return earthInstance
}
