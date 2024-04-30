class Solution:
    def rangeSum(self, nums: List[int], n: int, left: int, right: int) -> int:
        """
            n = len(nums)
            O(n) space O(right * log(n)) time
        """
        heap = [(num, i) for i, num in enumerate(nums)]
        heapify(heap)

        def minheapsum(n: int, nums: List[int], heap: List[Tuple[int, int]]):
            s = 0
            for _ in range(n):
                num, i = heappop(heap)
                if i + 1 < len(nums):
                    heappush(heap, (num + nums[i + 1], i + 1))
                s += num
            return s

        minheapsum(left - 1, nums, heap)
        return minheapsum(right - left + 1, nums, heap) % 1_000_000_007
