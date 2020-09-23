#include<stdio.h>
#include<stdlib.h>
/*oj又是错的，但是书上是这么写的？*/

int main()
{
	union 
	{
		int n;
		char s[5];
	}a;
	printf("输入一个数\n");
	scanf_s("%d", &a.n);
	for (int i = 0; i < sizeof(int); i++)
	{
		printf("%d的第%d字节编码是：%x\n", a.n, i + 1, a.s[i] & 0xff);
	}
	system("pause");
	return 0;
}