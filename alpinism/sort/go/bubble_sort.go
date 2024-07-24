package main

func BubbleSort(nums []int, len int) {
	var index int = len - 1
	var tmp int = 0
	for index > 0 {
		for j := 0; j < index; j++ {
			if nums[j] > nums[j+1] {
				tmp = j
				nums[j], nums[j+1] = nums[j+1], nums[j]
			}
		}
		index = tmp
		tmp = 0
	}
}
