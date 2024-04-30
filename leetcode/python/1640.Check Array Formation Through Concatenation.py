class Solution:
    def canFormArray(self, arr: List[int], pieces: List[List[int]]) -> bool:
        """
            n = len(arr)
            O(n) space O(n * log(n) + n) time
        """
        d = {num: i for i, num in enumerate(arr)}
        return all(map(lambda piece: piece[0] in d, pieces)) and\
            arr == list(chain.from_iterable(sorted(pieces, key=lambda piece: d[piece[0]])))
