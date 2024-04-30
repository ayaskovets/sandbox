class Solution:
    def mergeTrees(self, r1: TreeNode, r2: TreeNode) -> TreeNode:
        """
            n1 = vertices(r1)
            n2 = vertices(r2)
            O(max(n1 + n2)) stack space O(max(n1, n2)) time
        """
        return r2 if not r1 else\
              (r1 if not r2 else
              (TreeNode(r1.val + r2.val,
                        self.mergeTrees(r1.left, r2.left),
                        self.mergeTrees(r1.right, r2.right))))