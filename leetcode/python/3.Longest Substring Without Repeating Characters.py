class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        """
            n = len(s)
            O(1) space O(n) time
        """
        maxlen, l, r = 0, 0, 0
        d = {}
        for c in s:
            if c in d and d[c] >= l:
                maxlen = max(maxlen, r - l)
                l = d[c] + 1
            d[c] = r
            r += 1
        return max(maxlen, r - l)