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
    void levelOrder(TreeNode * root, int level, vector<vector<int>>& list) {
        if (!root) {
            return;
        }
        if (list.size() < level) {
            list.push_back(vector<int>(0));
        }
        list[level - 1].push_back(root->val);
        levelOrder(root->left, level + 1, list);
        levelOrder(root->right, level + 1, list);
        return;
    }
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> list(0);
        cout << "List size : " << list.size() << endl;
        levelOrder(root, 1, list);
        cout << "List size : " << list.size() << endl;
        for (int i = 0, j = list.size() - 1; i < j ; i++, j--) {
            vector<int> tmp = list[i];
            list[i] = list[j];
            list[j] = tmp;
        }
        return list;
    }
};