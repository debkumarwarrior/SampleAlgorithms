/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node * p1 = head;
        while (p1) {
            Node * p2 = p1->next;
            Node * p3 = new Node(p1->val);
            p1->next = p3;
            p3->next = p2;
            p1 = p2;
        }
        
        p1 = head;
        while (p1) {
            p1->next->random = (p1->random)? p1->random->next : nullptr;
            p1 = p1->next->next;
        }
        
        p1 = head;
        Node * p4 = nullptr, * p5 = nullptr, *nhead = nullptr;
        while (p1) {
            if (!p5) {
                p4 = p1->next;
                p1->next = p4->next;
                p5 = p4;
                nhead = p4;
            } else {
                p4 = p1->next;
                p1->next = p4->next;
                p5->next = p4;
                p5 = p4;
            }
            p1 = p1->next;
        }
        
        return nhead;
    }
};
