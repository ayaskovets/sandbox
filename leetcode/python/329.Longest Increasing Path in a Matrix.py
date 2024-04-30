class Solution:
    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        """
            m = len(matrix)
            n = len(matrix[0])
            O(m * n) space O(m * n) time
        """
        m, n = len(matrix), len(matrix[0])
        @cache
        def dfs(i: int, j: int):
            nonlocal matrix, m, n
            path, val = 1, matrix[i][j]
            if i > 0 and val < matrix[i - 1][j]:
                path = 1 + dfs(i - 1, j)
            if j > 0 and val < matrix[i][j - 1]:
                path = max(path, 1 + dfs(i, j - 1))
            if i < m - 1 and val < matrix[i + 1][j]:
                path = max(path, 1 + dfs(i + 1, j))
            if j < n - 1 and val < matrix[i][j + 1]:
                path = max(path, 1 + dfs(i, j + 1))
            return path
        return max([dfs(i, j) for i in range(m) for j in range(n)])
