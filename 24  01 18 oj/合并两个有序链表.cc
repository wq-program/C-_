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
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head=new ListNode();
        ListNode* ret=head;
        ListNode*l1=list1;
        ListNode*l2=list2;
        while(l1&&l2)
        {
            if(l1->val<l2->val)
            {
                head->next=l1;
                l1=l1->next;
            }
            else
            {
                head->next=l2;
                l2=l2->next;
            }
            head=head->next;
        }
        if(l2)head->next=l2;
        if(l1)head->next=l1;
        return ret->next;
    }
};