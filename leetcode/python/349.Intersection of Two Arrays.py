class Solution:
    def intersection(self, nums1: List[int], nums2: List[int]) -> List[int]:
        """
            n1 = len(nums1)
            n2 = len(nums2)
            O(n1 + n2) space O(n1 + n2) time
        """
        return set(nums1) & set(nums2)