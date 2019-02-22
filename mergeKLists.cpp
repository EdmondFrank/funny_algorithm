#include "DataStruct.h"
class Solution
{
public:
static bool cmp(const ListNode*a,const ListNode *b){
    return a->val<b->val;
}
    ListNode * mergeKLists(std::vector<ListNode*>& lists){
        std::vector<ListNode *> node_vec;
        for (int i=0;i<lists.size();i++){
            ListNode* head = lists[i];
            while(head){
                node_vec.push_back(head);
                head = head->next;
            }
            
        }
        if(node_vec.size()==0){
            return NULL;
        }
        std::sort(node_vec.begin(),node_vec.end(),cmp);
        for(int i=1;i<node_vec.size();i++)
        {
            node_vec[i-1]->next=node_vec[i];
        }
        node_vec[node_vec.size()-1]->next=NULL;
        return node_vec[0];
    }
    ListNode* mergeTwoLists(ListNode *l1,ListNode *l2){
        ListNode tmp_head(0);
        ListNode* pre = &tmp_head;
        while(l1 && l2){   
            if(l1->val < l2->val){
                //printf("l1 test merge\n");
                pre->next = l1;
                l1 = l1->next;
                
            }else
            {
                //printf("l2 test merge\n");
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
    ListNode *mergeKLists2(std::vector<ListNode*>& lists){
        if(lists.size()==0){
            return NULL;
        }
        if(lists.size()==1)
        {
            return lists[0];
        }
        if(lists.size()==2){
            return mergeTwoLists(lists[0],lists[1]);
        }
        int mid = lists.size()/2;
        std::vector<ListNode*> sub1_lists;
        std::vector<ListNode*> sub2_lists;
        for(int i=0;i<mid;i++){
            sub1_lists.push_back(lists[i]);
        }
        for(int i=mid;i<lists.size();i++){
            sub2_lists.push_back(lists[i]);
        }
        ListNode *l1 = mergeKLists2(sub1_lists);
        ListNode *l2 = mergeKLists2(sub2_lists);

        return mergeTwoLists(l1,l2);

    }
};
int main(){
    ListNode a(1);
    ListNode b(4);
    ListNode c(6);
    ListNode d(0);
    ListNode e(5);
    ListNode f(7);
    ListNode g(2);
    ListNode h(3);
    a.next=&b;
    b.next=&c;
    d.next=&e;
    e.next=&f;
    g.next=&h;
    Solution solve;
    std::vector<ListNode*> lists;
    lists.push_back(&a);
    lists.push_back(&d);
    lists.push_back(&g);
    clock_t start,end;
   
    start = clock();
    ListNode * head2 = solve.mergeKLists2(lists);
    end = clock();
    while(head2){
        printf("%d\n",head2->val);
        head2=head2->next;
    }
    printf("time of mergeKLists2: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
    
    start = clock();
    ListNode * head = solve.mergeKLists(lists);
    end = clock();
    while(head){
        printf("%d\n",head->val);
        head=head->next;
    }
    printf("time of mergeKLists: %f\n",(double)(end-start)/CLOCKS_PER_SEC);
    return 0;
    
}