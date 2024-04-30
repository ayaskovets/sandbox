class Solution:
    def relativeSortArray(self, arr1: List[int], arr2: List[int]) -> List[int]:
        """
            n1 = len(arr1)
            n2 = len(arr2)
            O(n1 + n2) space O(n2 + n1 * log(n1)) time
        """
        key = {n: i for i, n in enumerate(arr2)}
        return sorted(arr1, key=lambda n: key.get(n, 1000 + n))
