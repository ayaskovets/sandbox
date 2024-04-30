class Solution:
    def maxDepth(self, root: TreeNode) -> int:
        """
            n = vertices(root)
            O(n) stack space O(n) time
        """
        return 1 + max(self.maxDepth(root.left),
                       self.maxDepth(root.right)) if root else 0
