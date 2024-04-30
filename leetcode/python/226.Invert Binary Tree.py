class Solution:
    def invertTree(self, root: TreeNode) -> TreeNode:
        """
            n = vertices(root)
            O(n) stack space O(n) time
        """
        if root:
            root.left, root.right = self.invertTree(root.right), self.invertTree(root.left)
        return root
