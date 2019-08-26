#include<stdio.h>
#include<stdlib.h>

int main()
{
	double a = 0;
	while ((scanf_s("%lf",&a))&&a != -1)
	{
		double c = (200 + a*0.09) + 0.5;
		printf("%d\n", (int)c);
	}
	system("pause");
}