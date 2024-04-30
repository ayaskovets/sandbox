class Solution:
    def sortByBits(self, arr: List[int]) -> List[int]:
        """
            n = len(arr)
            O(n) space O(n * log(n)) time
        """
        return sorted(arr, key=lambda x: (bin(x).count('1'), x))
