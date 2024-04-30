class Solution:
    def maximumUnits(self, boxTypes: List[List[int]], truckSize: int) -> int:
        """
            n = len(boxTypes)
            O(n) space O(n * log(n)) time
        """
        boxTypes = sorted(boxTypes, key=itemgetter(1, 0), reverse=True)
        return sum(islice(chain.from_iterable(repeat(u, c) for c, u in boxTypes), truckSize))
