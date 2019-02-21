#include "DataStruct.h"
class Solution
{
public:
ListNode * getIntersectionNode(ListNode* headA,ListNode* headB){
    std::set<ListNode*> node_set;
    while(headA){
        node_set.insert(headA);
        headA= headA->next;
    }
    while(headB){
        if(node_set.find(headB)!=node_set.end()){
            return headB;
        }
        headB = headB->next;
    }
    return NULL;
}
int get_list_length(ListNode* head){
    int len =0;
    while(head){
        len++;
        head = head->next;
    }
    return len;
    
}
ListNode * forward_long_list(int long_len,int short_len,ListNode *head){
    int delta = long_len - short_len;
    while(head && delta){
        head=head->next;
        delta --;
    }
    return head;
}
ListNode * getIntersectionNode2(ListNode *headA,ListNode*headB){
    int lenA = get_list_length(headA);
    int lenB = get_list_length(headB);
    if(lenA>lenB){
        headA = forward_long_list(lenA,lenB,headA);
    }else
    {
        headB = forward_long_list(lenB,lenA,headB);
    }
    while(headA && headB){
        if(headA==headB){
            return headA;
        }
        headA = headA->next;
        headB = headB->next;
    }
    return NULL;
    
}
};
int main(){
    ListNode a1(1);
    ListNode a2(2);
    ListNode b1(3);
    ListNode b2(4);
    ListNode b3(8);
    ListNode c1(5);
    ListNode c2(6);
    ListNode c3(7);

    a1.next=&a2;
    a2.next=&c1;
    b1.next=&b2;
    b2.next=&b3;
    b3.next=&c1;
    c1.next=&c2;
    c2.next=&c3;
    Solution solve;
    
    printf("getIntersectionNode :\n");
        
    printf("%x %d\n",solve.getIntersectionNode(&a1,&b1),
    (solve.getIntersectionNode(&a1,&b1))->val);
    printf("getIntersectionNode2 :\n");
        
    printf("%x %d\n",solve.getIntersectionNode2(&a1,&b1),
    (solve.getIntersectionNode2(&a1,&b1))->val);
    return 0;
    
}