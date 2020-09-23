#include<stdio.h>
#include<stdlib.h>

int main()
{
	int a, b;
	scanf_s("%d%d", &a, &b);
	if (b%a==0)
	{
		printf("ÊÇ\n");
	}
	else
	{
		printf("²»ÊÇ\n");
	}
	system("pause");


}