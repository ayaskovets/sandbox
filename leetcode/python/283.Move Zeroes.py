class Solution:
    def moveZeroes(self, nums: List[int]) -> None:
        """
            n = len(nums)
            O(1) space O(n) time
        """
        pos = 0
        for num in nums:
            if num:
                nums[pos], pos = num, pos + 1
        nums[pos:] = repeat(0, len(nums) - pos)
