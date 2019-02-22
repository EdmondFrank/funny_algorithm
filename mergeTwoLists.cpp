#include "DataStruct.h"
class Solution
{
public:
    ListNode* mergeTwoLists(ListNode *l1,ListNode *l2){
        ListNode tmp_head(0);
        ListNode* pre = &tmp_head;
        while(l1 && l2){
            if(l1->val < l2->val){
                pre->next = l1;
                l1 = l1->next;
            }else
            {
                pre->next=l2;
                l2= l2->next;
            }
            pre = pre->next;
        }
        if(l1){
            pre->next = l1;
        }
        if(l2){
            pre->next=l2;
        }
        return tmp_head.next;
        
    }
};