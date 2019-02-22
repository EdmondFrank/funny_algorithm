#include"DataStruct.h"
//已知链表头指针head与数值x，将所有小于x的节点放在
//大于或等于x的节点前，且保持这些节点的原来的相对位置
class Solution
{
public:
    ListNode* partition(ListNode* head,int x){
        ListNode less_node(0);
        ListNode more_node(0);
        ListNode *less_ptr = &less_node;
        ListNode *more_ptr = &more_node;
        while(head){
            if(head->val<x){
                less_ptr->next=head;
                less_ptr=head;
            }else{
                more_ptr->next=head;
                more_ptr=head;
            }
            head=head->next;
        }
        less_ptr->next = more_node.next;
        more_ptr->next = NULL;
        return less_node.next;
        
    }
};
int main(){
    ListNode a(4);
    ListNode b(2);
    ListNode c(3);
    ListNode d(1);
    ListNode e(5);
    ListNode f(6);
    a.next=&b;
    b.next=&c;
    c.next=&d;
    d.next=&e;
    e.next=&f;
    Solution solve;
    ListNode *head = solve.partition(&a,3);
    while(head){
        printf("%d\n",head->val);
        head=head->next;
    }
    return 0;
    
}