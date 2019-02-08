#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10000
int a[MAX]={0};
int idx = 0;
void binary_search(int a[],int start,int end,double d,double r,int m,double v);
//d,m,n,r，v。例如：1.59,7,5,27.5，0.5,

int IsSwap(char* pBegin, char* pEnd)    //这部分是重点！！
{  
    char* p;  
    for (p=pBegin; p<pEnd; p++)  
    {  
        if (*p == *pEnd)  
            return 0;  
    }  
    return 1;  
}  
  
void Permutation(char* pStr, char* pBegin)  
{  
    if (*pBegin == '\0')
    {
        a[idx++] = strtol( pStr, NULL, 2 );
    printf("%s\n",pStr); 
        //cout << pStr <<endl; 
    }
    else  
    {  
        for (char* pCh = pBegin; *pCh!='\0'; pCh++)  
        {  
            if( IsSwap(pBegin,pCh)==1)  
            {  
                char temp = *pCh;    
                *pCh = *pBegin;    
                *pBegin = temp;    
  
                Permutation(pStr, pBegin+1);    
  
                temp = *pCh;    
                *pCh = *pBegin;    
                *pBegin = temp;    
            }  
        }  
    }  
} 

int main(int argc, char *argv[])
{
    //int a[10]={0};
    double d = 0,r=0,v=0;
    int m=0,n=0;

        FILE *fpRead=fopen("data.txt","r");
        if(fpRead==NULL)
        {
            return 0;
        }
            fscanf(fpRead,"%lf,",&d);
            fscanf(fpRead,"%d,",&m);
            fscanf(fpRead,"%d,",&n);
            fscanf(fpRead,"%lf,",&r);
            fscanf(fpRead,"%lf,",&v);
        fclose(fpRead);
            printf("%lf ",d);
            printf("%d ",m);
            printf("%d ",n);
            printf("%lf ",r);
            printf("%lf \n",v);
        //getchar();
        char * tmp = (char*)malloc((m+1)*sizeof(char));
        if(tmp==NULL) exit(1);

        for(int i = 0;i<m-n;i++)
            tmp[i]='0';
        for(int i = m-n;i<m;i++)
            tmp[i]='1';

        tmp[m]='\0';
        //printf("%s\n",tmp);
        //permute(tmp,0,m-1);
        Permutation(tmp,&tmp[0]);
    //printf("Hello World!\n");
    for(int i=0;i<idx;i++)
    {
        printf("%d\n",a[i]);
    }
    binary_search(a,0,idx,d,r,m,v);
    return 0;
}

void binary_search(int a[],int start,int end,double d,double r,int m,double v)
{
    int i,j,k,n,count;
    count=0;
    i=start;
    j=end;

    n=0;
    while(i<j)
    {
        n++;
        k=(i+j)/2;//这个为关键！！！！！
        int tmp = 1;
        double sum = 0;
        for(int i=0;i<m;i++)
        {
            //printf("%x ",(tmp<<i));
            //printf("%x ",87);
            //printf("%d\n",(tmp<<i)&87);
            sum +=(((tmp<<i)&a[k])>> i)*pow(d,i); 
        }
        // for(int i=0;i<7;i++)
        // {
        //     sum +=(tmp<<i)&a[k]*pow(1.59,i); 
        // }
        if(sum + v < r)
        {
            i=k+1;
        }
        if(sum - v > r)
        {
            j=k-1;
        }
        if(sum - r < v)
        {
            printf("you need: %d\n",a[k]);
            break;
        }
        
    }
    if(m==0)
        printf("failed\n");
    
}