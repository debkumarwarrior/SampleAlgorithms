#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode * p1 = head;
        while (n > 0) {
            p1 = p1->next;
            n--;
        }
        if (p1)
        {
            ListNode * p2 = head;
            while (p1->next) {
                p1 = p1->next;
                p2 = p2->next;
            }
            ListNode * p = p2->next;
            p2->next = p->next;
            delete p;
            return head;            
        }
        else
        {
            ListNode * p = head->next;
            delete head;
            return p;
        }
    }
};

int main()
{
	Solution * soln;
	ListNode * head1 = new List(1);
	ListNode * head2 = new List(2);
	ListNode * head3 = new List(3);
	ListNode * head4 = new List(4);
	ListNode * head5 = new List(5);
	ListNode * head6 = new List(6);
	
	head1->next = head2;
	head2->next = head3;
	head3->next = head4;
	head4->next = head5;
	head5->next = head6;
	
	soln.removeNthFromEnd(head1,2);
	return 0;
}
