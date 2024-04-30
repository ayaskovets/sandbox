class Solution:
    def kClosest(self, points: List[List[int]], k: int) -> List[List[int]]:
        """
            n = len(points)
            O(k) space O(n * log(k)) time
        """
        return nsmallest(k, points, key=lambda p: sqrt(p[0] ** 2 + p[1] ** 2))[:k]