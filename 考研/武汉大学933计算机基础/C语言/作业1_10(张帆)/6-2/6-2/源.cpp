#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*acm未通过，待修改*/



int main()
{
	int n, k = 1;
	double sum1, sum2;
	
	while (1)
	{
		printf("请输入a,b,c(无解输出NULL)\n");
		double a, b, c;
		scanf_s("%f%f%f", &a, &b, &c);
		if (a == 0)
		{
			if (b == 0)
			{
				printf("Case %d: NULL", k);
				k++;
			}
			else
			{
				printf("%.2lf", (-c / b));
				k++;
			}
		}
		else
		{
			if ((b*b - 4 * a*c)<0)
			{
				printf("Case %d: NULL", k);
				k++;
			}
			else
			{
				sum1 = ((-b + sqrt(b*b - 4 * a*c)) / (2 * a));
				sum2 = ((-b - sqrt(b*b - 4 * a*c)) / (2 * a));
				if (sum1 == sum2)
				{
					printf("Case %d: %.2lf\n", k, sum1);
					k++;
				}
				else
				{
					printf("Case %d: %.2lf ", k, sum2);
					printf("%.2lf\n", sum1);
					k++;

				}
			}
		}


	}
	system("pause");


}
