#include <iostream>
using namespace std;
typedef struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 }ListNode;

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right) {
            return head;
        }
        ListNode * p1 = nullptr, * p2 = head;
        for (int  i = 2; i <= left && p2; i++) {
            p1 = p2;
            p2 = p2->next;
        }
        ListNode * p3 = nullptr, * p4 = head;
        for (int  i = 2; i <= right && p4; i++) {
            p3 = p4;
            p4 = p4->next;
        }

        if (p1) {
            p1->next = nullptr;
        }
        ListNode * p5 = p4->next;
        p4->next = nullptr;
        
        ListNode * p6 = p2, * p7 = nullptr;
        while (p6) {
            ListNode * p = p6;
            p6 = p6->next;
            p->next = p7;
            p7 = p;
        }

        p6 = p7;
        while (p6->next) {
            p6 = p6->next;
        }
        p6->next = p5;

        if (p1) {
            p1->next = p7;
            return head;
        }
        return p7;
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    int TC;
    cin >> TC;
    for (int test = 1; test <= TC; test++) {
        int N;
        cin >> N;
        ListNode * head = nullptr, * prev = nullptr;
        for (int i = 0; i < N; i++) {
            ListNode * p = new ListNode();
            cin >> p->val;
            if (!head) {
                head = p;
                prev = p;
            } else {
                prev->next = p;
                prev = p;
            }
        }
        int left, right;
        cin >> left >> right;
        Solution soln;
        cout << "Input List : [ ";
        for (ListNode * p = head; p; p = p->next) {
            cout << p->val << " ";
        }
        cout << "]" << endl;
        cout << "Left : " << left << " Right : " << right << endl;

        cout << "Output List : [ ";
        for (ListNode * p = soln.reverseBetween(head, left, right); p; p = p->next) {
            cout << p->val << " ";
        }
        cout << "]" << endl;
        cout << endl << endl;
    }
    return 0;
}