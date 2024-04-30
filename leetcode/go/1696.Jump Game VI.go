func maxResult(nums []int, k int) int {
	/*
		n = len(nums)
		O(n) space O(n) time
	*/
	deq := make([]int, 1)
	for i := 1; i < len(nums); i++ {
			if deq[0] + k < i {
					deq = deq[1:]
			}
			nums[i] += nums[deq[0]]
			for len(deq) != 0 && nums[deq[len(deq) - 1]] <= nums[i] {
					deq = deq[:len(deq) - 1]
			}
			deq = append(deq, i)
	}
	return nums[len(nums) - 1]
}