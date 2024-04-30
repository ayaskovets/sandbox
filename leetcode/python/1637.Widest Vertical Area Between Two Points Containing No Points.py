class Solution:
    """
        n = len(points)
        O(n) space O(n * log(n) + n) time
    """
    def maxWidthOfVerticalArea(self, points: List[List[int]]) -> int:
        xp = sorted(map(itemgetter(0), points))
        return max(xp[i] - xp[i - 1] for i in range(1, len(points)))
