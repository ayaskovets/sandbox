class Solution:
    def isSubsequence(self, s: str, t: str) -> bool:
        """
            n1 = len(s)
            n2 = len(t)
            O(1) space O(n1 + n2) time
        """
        i = iter(t)
        return all(c in i for c in s)
