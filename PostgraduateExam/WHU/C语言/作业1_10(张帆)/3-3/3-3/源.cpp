#include<stdio.h>
#include<stdlib.h>

int main()
{
	double a, b;	//a=价格 b=支付
	printf("输入价格\n");
	scanf_s("%lf", &a);
	printf("输入支付的钱\n");	
	scanf_s("%lf",&b);
	printf("找钱数为%lf\n", a - b);
	system("pause");
}