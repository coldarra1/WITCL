#include<stdio.h>
#include<stdlib.h>
#define pi 3.141592

int main()
{
	printf("输入半径\n");
	double a;
	scanf_s("%lf", &a);
	printf("直径是%lf\n", 2 * a);
	printf("周长是%lf\n", 2 * pi*a);
	printf("面积是%lf\n", pi*a*a);
	system("pause");
}