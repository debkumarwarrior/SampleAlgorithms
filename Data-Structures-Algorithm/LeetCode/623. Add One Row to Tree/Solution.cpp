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
    TreeNode * addOneRow(TreeNode * root, int v, int d, int curr_depth, bool addleft) {
        if (curr_depth == d) {
            TreeNode * n = new TreeNode(v);
            if (addleft) {
                n->left = root;
            } else {
                n->right = root;
            }
            return n;
        } else {
            if (!root) {
                return nullptr;
            }
            root->left = addOneRow(root->left, v, d, curr_depth + 1, true);
            root->right = addOneRow(root->right, v, d, curr_depth + 1, false);
            return root;
        }
    }
public:
    TreeNode* addOneRow(TreeNode* root, int v, int d) {
        return addOneRow(root, v, d, 1, true);
    }
};
