class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        """
            n = len(nums)
            O(n) space O(n) time
        """
        return Counter(s) == Counter(t)
