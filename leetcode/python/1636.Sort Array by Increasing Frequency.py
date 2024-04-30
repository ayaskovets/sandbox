class Solution:
    def frequencySort(self, nums: List[int]) -> List[int]:
        """
            n = len(nums)
            O(n) space O(n * log(n) + n) time
        """
        freq = Counter(nums)
        return sorted(nums, key=lambda num: (freq[num], -num))