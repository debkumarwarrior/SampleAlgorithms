/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    ListNode * middle(ListNode * h) {
        ListNode * f = h, *s = h;
        while (f && f->next && s)
        {
            f = f->next->next;
            s = s->next;
        }
        return s;
    }
    ListNode * reverse(ListNode * h) {
        ListNode * p1 = h, * p2 = nullptr;
        while (p1) {
            ListNode * t = p1->next;
            p1->next = p2;
            p2 = p1;
            p1 = t;
        }
        return p2;
    }
public:
    bool isPalindrome(ListNode* head) {
        ListNode * mid = middle(head);
        ListNode * h1 = reverse(mid), * h2 = head;
        while (h1 && h2) {
            if (h1->val != h2->val) {
                return false;
            }
            h1 = h1->next;
            h2 = h2->next;
        }
        return true;
    }
};
