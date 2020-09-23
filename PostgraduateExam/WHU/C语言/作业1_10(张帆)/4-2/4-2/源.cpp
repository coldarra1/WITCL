#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n = 5, k = 2;
	double a=0;
	while (n--)
	{
		double sum = 1;
		for (int i =1; i <=k; i++)
		{
			sum = sum*i;
		}
		a = a + 1 / sum;
		k++;
		k++;
	}
	printf("½á¹ûÊÇ%lf", a);
	system("pause");
}