class Solution:
    def getAllElements(self, root1: TreeNode, root2: TreeNode) -> List[int]:
        """
            n1 = vertices(root1)
            n2 = vertices(root2)
            O(n1 + n2) space O(max(n1, n2)) time
        """
        def inorder(node: TreeNode) -> List[int]:
            return inorder(node.left) + [node.val] + inorder(node.right) if node else []
        return sorted(inorder(root1) + inorder(root2))
