#include<stdio.h>
#include<stdlib.h>

int main()
{
	double sum = 0;
	int a,b;
	while (scanf_s("%d%d",&a,&b))
	{
		switch (a)
		{
		case 1:
			sum = sum + 2.98*b;
			break;
		case 2:
			sum = sum + 4.50*b;
			break;
		case 3:
			sum = sum + 9.98*b;
			break;
		case 4:
			sum = sum + 4.49*b;
			break;
		case 5:
			sum = sum + 6.87*b;
			break;
		default:
			break;
		}	
		printf("%lf", sum);
	}
	printf("%lf", sum);

}