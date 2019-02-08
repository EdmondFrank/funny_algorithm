// 一个TXT文件，存放着5个参数：d,m,n,r，v。例如：1.59,7,5,27.5，0.5,
// 其中
// d允许小数，代表底数。
// m为整数，代表输出序列的位数。
// n为整数，代表输出序列中“1”的位数，
// r代表输出结果目标值，
// v代表输出结果计算目标值允许误差。
// 本示例中根据上述参考，转换出一个01序列满足如下
// 规则（1）与规则（2）：
// 规则（1）、输出一个TXT，例如a.txt，其结果为字符'0'或'1'序列：1010111，该序列满足m=共7位，满足n=其中有5个1
// 规则（2）、输出序列满足因子d的二进制规划计算后得出的目标值27.5在误差范围内，
// 例如d=1.59,对遍历所有7位序列中有5个1的序列，寻找一个序列：1010111，满足m=7位，n=5个1，
// 且按二进制计划规则结果为：
// 1*（1.59^6)+0*(1.59^5)+1*(1.59^4)+0*(1.59^3)+1*(1.59^2)+1*(1.59^1)+0*(1.59^0)=27.66,
// 该计算结果与r=27.5的误差为27.66-27.5=0.16，0.16<0.5，则寻找序列成功，程序输出r.txt=1010111
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10000

int a[MAX]={0};
int idx = 0;

void binary_Search(int a[],int start,int end,double d,double r,int m,double v);
void deciToBin(int num,FILE * fp);
int IsSwap(char* pBegin, char* pEnd);
void Permutation(char* pStr, char* pBegin);

int IsSwap(char* pBegin, char* pEnd)   
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
        //printf("%s\n",pStr); 
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

        Permutation(tmp,&tmp[0]);
    for(int i=0;i<idx;i++)
    {
        printf("%d\n",a[i]);
    }
    binary_Search(a,0,idx,d,r,m,v);
    return 0;
}
void deciToBin(int num,FILE * fp)
{
    if (num == 0){return;}
    deciToBin(num/2,fp);
    fprintf(fp, "%d", num%2);
}
void binary_Search(int a[],int start,int end,double d,double r,int m,double v)
{
    int i,j,k,n,count;
    count=0;
    i=start;
    j=end;

    n=0;
    while(i<j)
    {
        n++;
        k=(i+j)/2;
        int tmp = 1;
        double sum = 0;
        for(int i=0;i<m;i++)
        {
            sum +=(((tmp<<i)&a[k])>> i)*pow(d,i); 
        }
        if(sum + v < r)
        {
            i=k+1;
            continue;
        }
        if(sum - v > r)
        {
            j=k-1;
            continue;
        }
        if(sum - r < v)
        {
            printf("%lf\n",sum);
            printf("%lf\n",r);
            printf("%lf\n",sum-r);
            FILE *fp=fopen("r.txt","w");
            deciToBin(a[k],fp);
            fclose(fp);
            printf("you need string is :");
            deciToBin(a[k],stdout);
            
            //printf("you need: %d\n",a[k]);
            break;
        }
        
    }
    if(m==0)
        printf("failed\n");
    
}