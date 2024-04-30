class Solution:
    def largestPerimeter(self, nums: List[int]) -> int:
        """
            n = len(nums)
            O(n) space O(n * log(n) + n) time
        """
        nums = sorted(nums, reverse=True)
        for side in filter(lambda abc: abc[0] < abc[1] + abc[2], zip(nums, nums[1:], nums[2:])):
            return sum(side)
        return 0
