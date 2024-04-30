class Solution:
    def sortArrayByParityII(self, nums: List[int]) -> List[int]:
        """
            n = len(nums)
            O(n) space O(n) time
        """
        even, odd = filter(lambda n: n % 2 == 0, nums), filter(lambda n: n % 2 != 0, nums)
        return chain.from_iterable(zip(even, odd))