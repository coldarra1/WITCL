#include<stdio.h>
#include<stdlib.h>

int main()
{

	printf("输入重量\n");
	double a;
	scanf_s("%lf", &a);
	printf("%lf磅\n%lf克", a, (a * 454));
	system("pause");
}