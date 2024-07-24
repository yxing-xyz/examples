package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	// nums := make([]int, int(math.Pow10(8)))
	nums := make([]int, 20)
	rand.Seed(time.Now().UnixNano())
	for i := 0; i < len(nums); i++ {
		nums[i] = rand.Intn(len(nums))
	}
	fmt.Println("排序开始")
	start := time.Now()
	// BubbleSort(nums, len(nums))
	QuickSort(nums, 0, len(nums)-1)
	end := time.Now().Sub(start)
	fmt.Println(end)
	fmt.Println(nums)
}
