class Solution:
    def singleNumber(self, nums: List[int]) -> int:
        """
            n = len(nums)
            O(1) space O(n) time
        """
        return reduce(xor, nums)
