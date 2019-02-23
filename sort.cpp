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
void shellsort(int a[],int n){
    int i,j,g;
    int tmp,k;
    g = n/2;
    while(g!=0){
        for(i=g;i<n;i++){
            tmp=a[i];
            j = i-g;
            while(j>=0){
                k = j+g;
                if(a[j]>a[k])
                {
                    tmp=a[j];
                    a[j]=a[k];
                    a[k]=tmp;
                }
                j = j-g;
                
            }
        }
        g=g/2;
    }

}

int main(){
    int a [] ={6,1,2,7,9,3,4,5,10,8};
    int length = sizeof(a)/sizeof(int);
    //printf("length:%d\n",length);
    quicksort(0,length-1,a);
    for(int i=0;i<length;i++){
        printf("%d\n",a[i]);
    }
    shellsort(a,length);
    for(int i=0;i<length;i++){
        printf("%d\n",a[i]);
    }
}