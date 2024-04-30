func jump(nums []int) int {
	/*
		n = len(nums)
		O(1) space O(n) time
	*/
	if len(nums) < 2 {
			return 0
	}

	lvlEnd := 0
	for i, lvl := 0, 1; ; lvl++ {
			nextLvlEnd := 0
			for ; i <= lvlEnd; i++ {
					if nextLvlEnd < i + nums[i] {
							nextLvlEnd = i + nums[i]
					}
					if nextLvlEnd >= len(nums) - 1 {
							return lvl
					}
			}
			lvlEnd = nextLvlEnd
	}
	return -1
}