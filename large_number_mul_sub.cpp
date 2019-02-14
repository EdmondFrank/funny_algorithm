#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void length(char a[], int &l, int &p)
{
	int i = 0;
	p = -1;
	while (a[i] != '\0') {
		if (a[i] == '.')
			p = i + 1;
		i++;
	}
	l = i;
	if (p == -1)
		p = l + 1;
}
void sub(char a[], char b[], int c)
{
	int i = 0;
	int la, lb, pa, pb,l,p;
	char ta[1000], tb[1000],r[1000];
	length(a, la, pa);
	length(b, lb, pb);
	p = (pa > pb ? pa : pb)-1;
	l = p+c;
	for (i = 0; i < l; i++) {
		if (pa + i <= p)
			ta[i] = '0';
		else if (i < p)
			ta[i] = a[i + pa - p - 1];
		else if (i - p < la - pa)
			ta[i] = a[pa + i - p];
		else
			ta[i] = '0';
		if (pb + i <= p)
			tb[i] = '0';
		else if (i < p)
			tb[i] = b[i + pb - p - 1];
		else if (i - p < lb - pb)
			tb[i] = b[pb + i - p];
		else
			tb[i] = '0';
		r[i] = '0';
	}
	ta[i] = '\0';
	tb[i] = '\0';
	r[i] = '\0';
	int m = 0;
	if (strcmp(ta, tb) < 0)
		m = 1;
	int k=0;
	for (i = l - 1; i >= 0; i--) {
		if (m == 0) {
			if (ta[i] - k >= tb[i]) {
				r[i] = ta[i] - k - tb[i] + 48;
				k = 0;
			}
			else {
				r[i] = ta[i] - k - tb[i] + 10 + 48;
				k = 1;
			}
		}
		else {
			if (tb[i] - k >= ta[i]) {
				r[i] = tb[i] - k - ta[i] + 48;
				k = 0;
			}
			else {
				r[i] = tb[i] - k - ta[i] + 10 + 48;
				k = 1;
			}
		}
	}
	printf("减法结果:");
	if (m == 1)
		printf("-");
	for (i = 0; i < l; i++) {
		if (i == l - c)
			printf(".");
		printf("%c", r[i]);
	}
	printf("\n");
}
void mul(char a[], char b[], int c)
{
	char t[1000];
	t[0] = '0';
	t[1] = '\0';
	int la, pa, lb, pb,lc;
	length(a, la, pa);
	length(b, lb, pb);
	lc = la + lb - 2-1;
	int *p;
	int i=0;
	p = (int*)malloc(sizeof(int)*lc);
	for ( i = 0; i < lc; i++) {
		p[i] = 0;
	}
	int k1 = 0, k2 = 0;

	for ( i = 0; i <la; i++) {
		if (a[la-1-i] == '.' || a[la-1-i] == '0') {
			if (a[la-1-i] == '.')
				k1 = 1;
			continue;
		}
		k2 = 0;
		for (int j = 0; j < lb; j++) {
			if (b[lb-1-j] == '.' || b[lb-1-j] == '0') {
				if (b[lb-1-j] == '.')
					k2 = 1;
				continue;
			}
			p[lc - i - j+k1+k2-1] = p[lc - i - j+k2+k1-1] + (a[la - i - 1]-48) * (b[lb - j - 1]-48);
		}
	}
	for ( i = 0; i < lc + 2; i++)
		a[i] = '0';
	for ( i = lc - 1; i > 0; i--) {
		p[i - 1] = p[i - 1] + p[i] / 10;
		p[i] = p[i] % 10;
	}
	a[0] = p[0] / 10 + 48;
	a[1] = p[0] % 10+48;
	a[lc + 2] = '\0';
	k1 = 0;
	k2 = 0;
	for ( i = 0; i < lc ; i++) {
		if (i == (lc -1- (la - pa) - (lb - pb))) {
			a[i + 2] = '.';
			k1 = 1;
		}
		else {
			if (k1==1)
				k2++;
			a[i + 2] = p[i+1-k1] + 48;
			if (k2 == c) {
				a[i + 3] = '\0';
				break;
			}
		}
	}
	k1 = 0;
	for ( i = 0; i < lc + 2; i++) {
		if (a[i] == '0')
			k1++;
		else
			break;
	}
	for ( i = 0; i < lc + 2 - k1; i++) {
		a[i] = a[i + k1];
	}
	a[lc + 2 - k1] = '\0';
}
void power(char a[], int p, int c)
{
	char r[1000];
	r[0] = '1';
	r[1] = '.';
	r[2] = '0';
	r[3] = '\0';
	for (int i = 0; i < p; i++)
		mul(r, a, c);
	printf("幂运算结果为:%s\n", r);
}
int main(void)
{
	char a[1000], b[1000];
	int p;
	int c;
	printf("请输入运算数a:\n");
	scanf("%s", a);
	getchar();
	printf("请输入运算数b:\n");
	scanf("%s", b);
	printf("请输入小数点位数c:\n");
	scanf("%d", &c);
	getchar();
	sub(a, b, c);
	printf("请输入底数a:\n");
	scanf("%s", a);
	getchar();
	printf("请输入幂b:\n");
	scanf("%d", &p);
	getchar();
	printf("请输入小数点位数c:\n");
	scanf("%d", &c);
	getchar();
	power(a, p, c);
	system("pause");
	return 0;
}