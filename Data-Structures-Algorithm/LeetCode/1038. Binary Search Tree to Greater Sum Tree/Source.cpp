/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    void convert(TreeNode * root, int& curr) {
        if (!root) {
            return;
        }
        convert(root->right, curr);
        curr += root->val;
        root->val = curr;
        convert(root->left, curr);
    }
public:
    TreeNode* bstToGst(TreeNode* root) {
        int curr = 0;
        convert(root, curr);
        return root;
    }
};
