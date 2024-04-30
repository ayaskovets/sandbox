class Solution:
    def pancakeSort(self, arr: List[int]) -> List[int]:
        """
            n = len(arr)
            O(n) space O(n ^ 2) time
        """
        l = []
        for mx in range(len(arr), 1, -1):
            i = arr.index(mx)
            l.extend([i + 1, mx])
            arr = arr[:i:-1] + arr[:i]
        return l
