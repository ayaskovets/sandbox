/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode *TreeNode_new(int val, struct TreeNode *left, struct TreeNode *right) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = left;
    node->right = right;
    return node;
}

struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize){
    /*
        n = preorderSize
        O(n) space O(n) time
    */
    if (!preorderSize) {
        return NULL;
    }

    int m;
    for (int i = 0; i < inorderSize; ++i) {
        if (inorder[i] == preorder[0]) {
            m = i;
            break;
        }
    }

    return TreeNode_new(preorder[0],
        buildTree(preorder + 1, m, inorder, m),
        buildTree(preorder + 1 + m, preorderSize - 1 - m, inorder + 1 + m, inorderSize - 1 - m));
}