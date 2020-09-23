#include<stdio.h>
#include<stdlib.h>

int main()
{
	double e=1,e2=0;
	printf("输入精度\n如0.1，0.01\n");
	double n;
	scanf_s("%lf", &n);

	for ( double i = 1;e-e2>n; i++)
	{
		double k=1;
		for (double x=1;x<=i;x++)
		{
			k = (1 / x)*k;
		}
		e2 = e;
		e = e + k;
	}
	printf("%lf", e);
	system("pause");


}