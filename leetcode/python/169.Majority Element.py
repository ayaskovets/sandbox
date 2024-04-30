class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        """
            n = len(nums)
            O(1) space O(n) time
        """
        cnt, maj = 1, nums[0]
        for i in range(1, len(nums)):
            cnt += 1 if nums[i] == maj else -1
            if cnt == 0:
                cnt, maj = 1, nums[i]
        return maj
