#include<stdlib.h>
#include<stdio.h>
#include<math.h>
double f(int x)
{
	return sqrt(6 * x + 2);
}

int main()
{
	double a, b = 0;
	int i = 0;
	for (; i <= 1000;)
	{
		a = f(i);
		printf("%.4f ", a);
		printf("%.4f\n", a + b);
		b = b + a;
		i = (i + 50);
	}
	system("pause");
}