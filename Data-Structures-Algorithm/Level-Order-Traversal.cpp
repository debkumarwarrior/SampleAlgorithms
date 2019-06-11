/*
You are given a pointer to the root of a binary tree. You need to print the level order traversal of this tree. In level order traversal, we visit the nodes level by level from left to right. You only have to complete the function. For example:

     1
      \
       2
        \
         5
        /  \
       3    6
        \
         4 
		 
For the above tree, the level order traversal is 1 -> 2 -> 5 -> 3 -> 6 -> 4.
*/

#include <bits/stdc++.h>	

using namespace std;

class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};

class Solution {
    public:
  		Node* insert(Node* root, int data) {
            if(root == NULL) {
                return new Node(data);
            } else {
                Node* cur;
                if(data <= root->data) {
                    cur = insert(root->left, data);
                    root->left = cur;
                } else {
                    cur = insert(root->right, data);
                    root->right = cur;
               }

               return root;
           }
        }
/*
class Node {
    public:
        int data;
        Node *left;
        Node *right;
        Node(int d) {
            data = d;
            left = NULL;
            right = NULL;
        }
};
*/
    void levelOrder(Node * root) {

        if (!root) {
            return;
        }
        Node * queue[501];
        int front = 0;
        int rear = 0;
        queue[rear] = root;
        rear++;

        while (front < rear) {
            Node * t = queue[front];
            front++;

            cout << t->data << " ";
            if (t->left) {
                queue[rear] = t->left;
                rear++;
            }
            if (t->right) {
                queue[rear] = t->right;
                rear++;
            }
        }
        cout << endl;
    }

}; //End of Solution

int main() {
  
    Solution myTree;
    Node* root = NULL;
    
    int t;
    int data;

    std::cin >> t;

    while(t-- > 0) {
        std::cin >> data;
        root = myTree.insert(root, data);
    }
  
	myTree.levelOrder(root);
    return 0;
}
