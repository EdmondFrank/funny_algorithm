// 一个TXT文件，存放着5个参数：d,m,n,r，v。例如：1.59,7,5,27.5,0.5,
// 其中
// d允许小数，代表底数。
// m为整数，代表输出序列的位数。m<=10000
// n为整数，代表输出序列中“1”的位数，n<=1000
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
const long MAX=1000000;
int *a;
int idx = 0;

void binary_Search(int a[],int start,int end,double d,double r,int m,double v);
void binary_Search2(unsigned long start,long end,double d,double r,int m,int n,double v);
void deciToBin(long num,FILE * fp);
int IsSwap(char* pBegin, char* pEnd);
void Permutation(char* pStr, char* pBegin);
double getSum(long k,int m,double d);
void quickSort( int a[], int idx,int m,double d);
long Factorial(int n, int m);
long Factorial(int n, int m)
{
    //printf("%d %d",n,m);
	long isum = 1;
	//  if(m < n-m) m = n-m;
	
   for(int k=1;k<=n;k++)
   {
       isum=(isum*(m-n+k))/k;//先算乘法，避免先算（m-n+k）/k除不尽带来误差
    }
	return isum;
	  
}

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
       // printf("%s\n",pStr);
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
long BitCount(long n)
{
    long c =0 ; // 计数器
    for (c =0; n; n >>=1) // 循环移位
        c += n &1 ; // 如果当前位是1，则计数器加1
    return c ;
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

            printf("d is : %lf\n",d);
            printf("m is : %d\n",m);
            printf("n is : %d\n",n);
            printf("r is : %lf\n",r);
            printf("v is : %lf\n",v);
        //getchar();
        char * start = (char*)malloc((m+1)*sizeof(char));
        char * end = (char*)malloc((m+1)*sizeof(char));
        if(start==NULL) exit(1);
        if(end==NULL) exit(1);

        for(int i = 0;i<m-n;i++)
            start[i]='0';
        for(int i = m-n;i<m;i++)
            start[i]='1';

        for(int i = 0;i<m-n;i++)
            end[i]='1';
        for(int i = m-n;i<m;i++)
            end[i]='0';
        printf("start : %s,%ld\n",start,strlen(start));
        printf("end : %s,%ld\n",end,strlen(end));
        start[m]='\0';
        end[m]='\0';
    
    //     for(int i=0;i<idx;i++)
    //     {
    //         printf("%d %d\n",i,a[i]);
    //     }
    //
    long max = Factorial(n,m);
    printf("Factorial:%ld\n",max);
    a = (int*)malloc((max+1)*sizeof(int));
    if (d<2 && max<MAX)
    {
        printf("d is less than 2\n");
        Permutation(start,&start[0]);
        binary_Search(a,0,idx,d,r,m,v);
    }
    else
    {
        printf("d is greater than 2\n");
        binary_Search2(strtol(start, NULL, 2 ),strtol(end, NULL, 2 ),d,r,m,n,v);
    }
    
   
    return 0;
}

void deciToBin(long num,FILE * fp)
{
    if (num == 0){return;}
    deciToBin(num/2,fp);
    fprintf(fp, "%ld", num%2);
}
void binary_Search2(unsigned long start,long end,double d,double r,int m,int n,double v)
{
    long i,j,count;
    long k;
    count=0;
    i=start;
    j=end;
    //int x = 0;
    printf("start %ld end: %ld\n",start,end);
    while(i<j)
    {
        k=(i+j)/2;
        while(BitCount(k)!=n){k--;}
        if(k>j)break;
        double sum =getSum(k,m,d);
        printf("i:%ld j:%ld K:%ld sum:%lf\n",i,j,k,sum);
        // for(int i=0;i<m;i++)
        // {
        //     sum +=(((1<<i)&k)>> i)*pow(d,i);
        // }
        //printf("%lf\n",sum-r);
        
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
        

        if(sum - r < v && BitCount(k)==n)
        {
            count++;
            
            //printf("%lf\n",r);
            //printf("%lf\n",sum-r);
            FILE *fp=fopen("r.txt","w");
            deciToBin(k,fp);
            fclose(fp);
            printf("you need string is :");
            deciToBin(k,stdout);
            printf("\n");
            //printf("%ld",strlen(k));
            printf("num of 1 is: %ld\n",BitCount(k));
            printf("it's sum is :%lf\n",sum);

            //printf("you need: %d\n",k);
            break;
        }

    }
    if(count==0)
        printf("no exist\n");

}
double getSum(long k,int m,double d)
{
    double sum = 0;
    //printf("i:%d j:%d K:%d\n",i,j,k);
    for(int i=0;i<m;i++)
    {
        sum +=(((1<<i)&k)>> i)*pow(d,i);
    }
    return sum;
}
void quickSort( int a[], int idx,int m,double d)
{
    int i, j, p, tmp;
    if (idx < 2)  return;

    p = a[idx / 2];   // Get the middle element as pivot ..

    for ( i = 0, j = idx -1;; i++, j--) {
        while (getSum(a[i],m,d) < getSum(p,m,d))
            i++;
        while (getSum(p,m,d) < getSum(a[j],m,d))
            j--;
        if ( i >= j)
            break;
        tmp = a[i]; a[i] = a[j]; a[j] = tmp;    //swap both ..
    }   

    quickSort( a, i,m,d); 
    quickSort( a + i, idx - i,m,d); 
}

void binary_Search(int a[],int start,int end,double d,double r,int m,double v)
{
    int i,j,k,count;
    count=0;
    i=start;
    j=end;

    printf("begin to sort n:%d\n",end);
    quickSort(a,idx,m,d);
    // for(int x=1;x<idx;x++)
    // {
    //     //double cur = getSum(a[x],m,d);
    //     int y,temp=0;
    //     temp = a[x];
	// 	for(y = x - 1; y >= 0; y --)
	// 	{
    //         /**/
	// 		//if(b[y] > b[x]/*getSum(temp,m,d)*/)
	// 		if(getSum(a[y],m,d) > getSum(temp,m,d))
    //         {
	// 			a[y + 1] = a[y];	
	// 		}else
	// 		{
	// 			break;
	// 		}
	// 	}
	// 	a[y + 1] = temp;
    // }
    // for(int x=0;x<idx;x++)
    // {
    //     printf("%lf\n",getSum(a[x],m,d));
    // }
    while(i<=j)
    {
        k=(i+j)/2;
        double sum = getSum(a[k],m,d);
        //printf("i:%d j:%d K:%d value:%d\n",i,j,k,a[k]);
        //printf("sum : %lf\n",sum);
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
            count++;
            FILE *fp=fopen("r.txt","w");
            deciToBin(a[k],fp);
            fclose(fp);
            printf("you need string is :");
            deciToBin(a[k],stdout);
            printf("\n");
            printf("num of 1 is: %ld\n",BitCount(a[k]));
            printf("it's sum is :%lf\n",sum);
           //printf("you need: %d\n",a[k]);
            break;
        }
        
    }
    if(count==0)
        printf("no exist\n");
    
}
