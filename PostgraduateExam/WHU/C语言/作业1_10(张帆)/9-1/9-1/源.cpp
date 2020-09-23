#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>



typedef struct point
{
	double x;
	double y;
}POINT;
typedef struct circle
{
	double m;
	double n;
	double r;
}CIRCLE;

int in_circle(POINT p, CIRCLE c)
{
	double len;
	len = ((p.x - c.m)*(p.x - c.m) + (p.y - c.n)*(p.y - c.n) - (c.r)*(c.r));
	if (len>0.0)
	{
		return 0;
	}
	if (len<0.0)
	{
		return 2;
	}
	if (len == 0.0)
	{
		return 1;
	}

}

int main()
{
	POINT dian;
	CIRCLE yuan;
	while (1)
	{
		scanf("%lf%lf%lf%lf%lf", &dian.x,&dian.y,&yuan.m,&yuan.n, &yuan.r);
		printf("%d\n", in_circle(dian, yuan));
	}

	//system("pause");
}