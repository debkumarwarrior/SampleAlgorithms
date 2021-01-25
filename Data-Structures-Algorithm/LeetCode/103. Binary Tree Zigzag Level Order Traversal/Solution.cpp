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
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<TreeNode*>> stacks(0);
        vector<vector<int>> values(0);
        int current_level = 0;
        
        bool leftToRight = true;
        if (root) {
            stacks.push_back(vector<TreeNode *>(0));
            stacks[0].push_back(root);
        }
        
        while (current_level < stacks.size()) {
            cout << "Current Level : " << current_level << endl;
            if (stacks[current_level].size() > 0) {
                values.push_back(vector<int>(0));
                stacks.push_back(vector<TreeNode*>(0));
            }
            for (int i = stacks[current_level].size() - 1; i >= 0; i--) {
                if (stacks[current_level][i]) {
                    cout << stacks[current_level][i]->val << " ";
                } else {
                    cout << "NULL";
                }
                cout << endl;
                values[current_level].push_back(stacks[current_level][i]->val);
                if (leftToRight) {
                    if (stacks[current_level][i]->left) {
                        stacks[current_level + 1].push_back(stacks[current_level][i]->left);
                    }
                    if (stacks[current_level][i]->right) {
                        stacks[current_level + 1].push_back(stacks[current_level][i]->right);
                    }
                } else {
                    if (stacks[current_level][i]->right) {
                        stacks[current_level + 1].push_back(stacks[current_level][i]->right);
                    }
                    if (stacks[current_level][i]->left) {
                        stacks[current_level + 1].push_back(stacks[current_level][i]->left);
                    }
                }
            }
            leftToRight = !leftToRight;
            current_level++;
        }
        return values;
        
    }
};
