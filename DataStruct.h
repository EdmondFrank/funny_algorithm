#include<iostream>
#include <stdio.h>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
struct ListNode
{
    int val;
    ListNode * next;
    ListNode(int x):val(x),next(NULL){}
};
struct RandomListNode{
    int label;
    RandomListNode *next,*random;
    RandomListNode(int x):label(x),next(NULL),random(NULL){}
};
