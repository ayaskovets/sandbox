class Solution:
    def runningSum(self, nums: List[int]) -> List[int]:
        """
            n = len(nums)
            O(n) space O(n) time
        """
        return accumulate(nums)
