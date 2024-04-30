class Solution:
    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        """
            n1 = len(l1)
            n2 = len(l2)
            O(max(n1, n2)) space O(max(n1, n2)) time
        """
        class ListIter():
            def __init__(self, l: ListNode):
                self.l = ListNode(next=l)
            def __iter__(self):
                return self
            def __next__(self):
                self.l = self.l.next
                if self.l:
                    return self.l.val
                raise StopIteration
        
        l3 = ListNode()
        li, rem = l3, False
        for n1, n2 in zip_longest(ListIter(l1), ListIter(l2)):
            li.next = ListNode()
            li = li.next
            s = (n1 if n1 else 0) + (n2 if n2 else 0) + rem
            li.val, rem = (s - 10, True) if s >= 10 else (s, False)
        if rem:
            li.next = ListNode(1)
        return l3.next