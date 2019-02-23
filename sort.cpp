#include <stdio.h>
//排序算法综合

void quicksort(int begin,int end,int a[]){
    int i,j,tmp;
    if(begin>=end) return;
    i=begin;
    j=end;
    tmp=a[i];
    while(i!=j){
       while(a[j]>tmp && j>i){
           j--;
       }
       if(i<j){
           a[i]=a[j];
           i++;
       } 
       while(a[i]<tmp && j>i){
           i++;
       }
       if(i<j){
           a[j]=a[i];
           j--;
       } 
       
    }
    a[i]=tmp;
    //printf("a[%d]=%d\n",i,tmp);
    quicksort(begin,j-1,a);
    quicksort(i+1,end,a);
}
int main(){
    int a [] ={6,1,2,7,9,3,4,6,10,8};
    int length = sizeof(a)/sizeof(int);
    //printf("length:%d\n",length);
    quicksort(0,length-1,a);
    for(int i=0;i<length;i++){
        printf("%d\n",a[i]);
    }
}