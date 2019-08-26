#include<stdio.h>
#include<stdlib.h>

int main()
{
	double a;
	printf("输入英里\n");
	scanf_s("%lf", &a);
	printf("%lf公里\n", (a * 5280 * 12 * 2.54) / 100000);
	system("pause");


}