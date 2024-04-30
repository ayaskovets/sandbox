class Solution:
    def diagonalSort(self, mat: List[List[int]]) -> List[List[int]]:
        """
            m = len(mat)
            n = len(mat[0])
            d = m + n - 3
            O(m * n) space O(d * min(m, n) * log(min(m, n))) time
        """
        def diagonals(mat: List[List[int]]):
            m, n = len(mat), len(mat[0])
            for d in range(2 - m, n - 1):
                yield list(zip(range(-min(0, d), m), range(max(0, d), n)))
        for diagonal in diagonals(mat):
            dsorted = sorted([mat[r][c] for r, c in diagonal])
            for r, c in diagonal:
                mat[r][c] = dsorted.pop(0)
        return mat
