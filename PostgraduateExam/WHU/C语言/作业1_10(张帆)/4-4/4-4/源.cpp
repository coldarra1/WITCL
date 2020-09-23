#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
	double pi=0,a=1;
	int n = 0;
	while ((1/a)>(10E-6))
	{
		pi = pi + pow(-1, n)*(1 / a);
		n++;
		a = a + 2;
	}
	printf("%lf", pi * 4);
	system("pause");
}