#include <stdio.h>

void GCDLCM();

int main()
{
	int a,b;
	int gcd,lcm;

	scanf("%d %d",&a,&b);

	GCDLCM(a,b,&gcd,&lcm);

	printf("%d %d\n",gcd,lcm);

	return 0;
}

void GCDLCM(int a,int b,int *gcd,int *lcm)
{
	int m,n,r;

	m=a;n=b;

	do
	{
		r=m%n;m=n;n=r;
	}
	while(r!=0);

	*gcd=m;
	*lcm=(a*b)/m;
}

