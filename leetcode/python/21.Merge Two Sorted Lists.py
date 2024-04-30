class Solution:
    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        """
            n1 = len(l1)
            n2 = len(l2)
            O(max(n1, n2)) stack space O(max(n1, n2)) time
        """
        return l1 if not l2 else\
              (l2 if not l1 else
              (ListNode(l1.val, self.mergeTwoLists(l1.next, l2)) if l1.val < l2.val else
               ListNode(l2.val, self.mergeTwoLists(l1, l2.next))))