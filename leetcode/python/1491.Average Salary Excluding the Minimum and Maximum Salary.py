class Solution:
    def average(self, salary: List[int]) -> float:
        """
            n = len(salary)
            O(1) space O(n) time
        """
        div = len(salary) - 2
        return sum(map(lambda x: x / div, salary)) - min(salary) / div - max(salary) / div