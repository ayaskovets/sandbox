class Solution:
    def getKth(self, lo: int, hi: int, k: int) -> int:
        """
            n = hi - lo + 1
            O(n) space O(n * log(n) + n) time
        """
        @cache
        def power(x):
            if x == 1:
                return 0
            return 1 + power(x // 2 if x % 2 == 0 else 3 * x + 1)
        return sorted(range(lo, hi + 1), key=lambda x: (power(x), x))[k - 1]
