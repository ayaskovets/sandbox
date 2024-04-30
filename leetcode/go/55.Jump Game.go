func canJump(nums []int) bool {
	/*
		n = len(nums)
		O(1) space O(n) time
	*/
	n := 0
	for i := 0; i < len(nums) - 1; i += 1 {
			if nums[i] == 0 && n <= i {
					return false
			}
			if n < i + nums[i] {
					n = i + nums[i]
			}
	}
	return true
}