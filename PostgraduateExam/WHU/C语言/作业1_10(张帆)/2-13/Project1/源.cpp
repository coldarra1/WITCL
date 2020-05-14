#include<stdio.h>
#include<stdlib.h>
int main()
{
	int a, b;
	printf("请输入两个整数");
	scanf_s("%d%d", &a, &b);
	printf("和是%d\n", a + b);
	printf("乘积是%d\n", a *b);
	printf("差是%d\n", a - b);
	if (b!=0)
	{
		printf("商是%d\n", a / b);
		printf("余数是%d\n", a%b);
	}

	system("pause");
	return 0;
	



 }