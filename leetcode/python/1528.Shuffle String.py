class Solution:
    def restoreString(self, s: str, indices: List[int]) -> str:
        """
            n = len(s)
            O(n) space, O(n) time
        """
        restored = [''] * len(s)
        for e, i in enumerate(indices):
            restored[i] = s[e]
        return ''.join(restored)
