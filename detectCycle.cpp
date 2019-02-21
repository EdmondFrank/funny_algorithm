#include"DataStruct.h"
class Solution
{
public:
ListNode * detectCycle(ListNode * head){
    std::set<ListNode*> node_set;
    while(head){
        if(node_set.find(head)!= node_set.end())
        {
            return head;
        }
        node_set.insert(head);
        head = head->next;
    }
    return NULL;
    }
    ListNode * detectCycle2(ListNode *head){
        ListNode * fast = head;
        ListNode * slow = head;
        ListNode * meet = NULL;
        while(fast){
            slow = slow->next;
            fast = fast->next;
            if(!fast){
                return NULL;
            }
            fast = fast->next;
            if(fast == slow){
                meet = fast;
                break;
            }
        }
            if(meet == NULL){
                return NULL;
            }
            while(head&&meet){
                if(head==meet){
                    return head;
                }
                head = head->next;
                meet = meet->next;
            }
            
        return NULL;
    }
};
int main(){
    ListNode a(1);
    ListNode b(2);
    ListNode c(3);
    ListNode d(4);
    ListNode e(5);
    ListNode f(6);
    ListNode g(7);

    a.next=&b;
    b.next=&c;
    c.next=&d;
    d.next=&e;
    e.next=&f;
    f.next=&g;
    g.next=&c;
    Solution solve;
    ListNode *node  = solve.detectCycle(&a);
    if(node)
    {
         printf("cycle start node:%x %d\n",node,node->val);
    }else
    {
        printf("no cycle");
    }
    node = NULL;
    node = solve.detectCycle2(&a);
    if(node)
    {
         printf("cycle start node:%x %d\n",node,node->val);
    }else
    {
        printf("no cycle");
    }
    return 0;
    
}
