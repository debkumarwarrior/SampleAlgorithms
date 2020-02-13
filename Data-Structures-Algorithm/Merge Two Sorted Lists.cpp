/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode * h = NULL, * p1 = NULL;
        while (l1 && l2) {
            ListNode * p2 = NULL;
            if (l1->val < l2->val) {
                p2 = l1;                
                l1 = l1->next;
                p2->next = NULL;
            } else {
                p2 = l2;
                l2 = l2->next;
                p2->next = NULL;
            }
            if (h == NULL) {
                h = p2;
                p1 = h;
            } else {
                p1->next = p2;
                p1 = p2;
            }            
        }
        ListNode * l = (l1)? l1 : (l2)? l2 : NULL;
        while (l) {
            ListNode * p2 = l;
            l = l->next;
            p2->next = NULL;
            if (h == NULL) {
                h = p2;
                p1 = h;
            } else {
                p1->next = p2;
                p1 = p2;
            }            
        }
        return h;        
    }
};
