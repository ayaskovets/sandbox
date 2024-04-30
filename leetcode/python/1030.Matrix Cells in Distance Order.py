class Solution:
    def allCellsDistOrder(self, R: int, C: int, r0: int, c0: int) -> List[List[int]]:
        """
            n = R * C
            O(n) space O(n * log(n)) time
        """
        return sorted([[i, j] for i in range(0, R) for j in range(0, C)],
            key=lambda p: abs(r0 - p[0]) + abs(c0 - p[1]))