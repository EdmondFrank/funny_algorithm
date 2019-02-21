#include "DataStruct.h"
class Solution{
    public:
        ListNode * reverseList(ListNode* head,int m,int n){
        int change_len = n-m+1;
        ListNode * prehead = NULL;
        ListNode *result = head;
        while(head && --m){
            prehead = head;
            head = head->next;
        }
        ListNode * modify_list_tail = head;
        ListNode * newhead = NULL;
        while(head && change_len){
            ListNode * next = head->next;
            head->next = newhead;
            newhead = head;
            head = next;
            change_len--;
        }
        modify_list_tail->next=head;
        if(prehead){
            prehead->next = newhead;
        }else
        {
            result=prehead;
        }
        
        
        
        }
};
int main(){
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);

    a.next=&b;
    b.next=&c;
    c.next=&d;
    d.next=&e;
    Solution solve;
    ListNode *head = &a;
    printf("Before reverse:\n");
    while(head){
        printf("%d\n",head->val);
        head = head->next;
    }
    head = solve.reverseList(&a,2,4);
    printf("After reverse:\n");
    while(head){
        printf("%d\n",head->val);
        head = head->next;
    }
    return 0;
    
}