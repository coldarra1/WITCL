#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double distance(double x1, double y1, double x2, double y2)
{
	double a;
	a = sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	return a;
}

int main()
	{
		double x1, y1, x2, y2, a;
		int n;
		scanf_s("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
		a = distance(x1, y1, x2, y2);
		printf("%.4f\n", a);
		system("pause");
	}

