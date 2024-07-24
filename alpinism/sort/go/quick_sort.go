package main

func QuickSort(nums []int, left, right int) {
	if left < right {
		privotIndex := partition(nums, left, right)
		QuickSort(nums, left, privotIndex-1)
		QuickSort(nums, privotIndex+1, right)
	}
}

func partition(nums []int, left, right int) int {
	privotValue := nums[left]
	swapIndex := left + 1
	for i := left + 1; i <= right; i++ {
		if nums[i] < privotValue {
			nums[swapIndex], nums[i] = nums[i], nums[swapIndex]
			swapIndex++
		}
	}
	swapIndex--
	nums[left], nums[swapIndex] = nums[swapIndex], nums[left]
	return swapIndex
}
