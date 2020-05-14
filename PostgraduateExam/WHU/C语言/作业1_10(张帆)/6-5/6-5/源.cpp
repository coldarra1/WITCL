#include<stdio.h>
#include<stdlib.h>

int main()
{
	double  a = 0, b, c;
	while (scanf_s("%lf", &a)&&a != -1)
	{
		scanf_s("%lf", &b);
		getchar();
		scanf_s("%lf", &c);   //利息 = 本金 × 利率 × 天数 / 365
		double sum;
		sum = a*(b / 100)*(c / 365);
		printf("%.2f\n", sum);

	}
	system("pause");
}