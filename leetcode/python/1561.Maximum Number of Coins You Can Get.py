class Solution:
    def maxCoins(self, piles: List[int]) -> int:
        """
            n = len(nums)
            O(n) space O(n * log(n) + n) time
        """
        piles = sorted(piles, reverse=True)
        return sum(piles[1:2 * len(piles) // 3:2])
