class Solution:
    """
        n = len(arr)
        O(n) space O(n * log(n) + n) time
    """
    def canMakeArithmeticProgression(self, arr: List[int]) -> bool:
        arr = sorted(arr)
        step = arr[1] - arr[0]
        return all(arr[i] - arr[i - 1] == step for i in range(1, len(arr)))
