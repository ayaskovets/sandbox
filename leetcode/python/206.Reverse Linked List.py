class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        """
            n = len(head)
            O(1) space O(n) time
        """
        cur, nxt = None, head
        while nxt:
            nxt.next, cur, nxt = cur, nxt, nxt.next
        return cur

class Solution:
    def reverseList(self, head: ListNode) -> ListNode:
        """
            n = len(head)
            O(n) stack space O(n) time
        """
        if head and head.next:
            nxt = self.reverseList(head.next)
            head.next.next, head.next = head, None
            return nxt
        return head