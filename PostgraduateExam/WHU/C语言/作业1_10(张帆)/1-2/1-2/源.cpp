#include<stdio.h>
#include<stdlib.h>
int main()
{
	printf("输入两个数\n");
	int a, b;
	scanf_s("%d%d", &a,&b);
	printf("和为%d\n",a + b);
	system("pause");
}