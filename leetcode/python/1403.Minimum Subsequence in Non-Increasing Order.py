class Solution:
    def minSubsequence(self, nums: List[int]) -> List[int]:
        """
            n = len(nums)
            O(n) space O(n * log(n) + n) time
        """
        nsum = sum(nums)
        nums = sorted(nums, reverse=True)
        minsub = lambda acc, n: (acc[0] + n, acc[1] + 1) if acc[0] <= nsum - acc[0] else acc
        return nums[:reduce(minsub, nums, (0, 0))[1]]
