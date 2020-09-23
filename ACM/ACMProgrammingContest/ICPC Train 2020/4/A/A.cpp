#include <stdio.h>

int n, a, b;

int main()
{
	scanf("%d %d %d", &a, &b, &n);
	printf("%d\n", (n-a-1)/(b-a)*2+1);
}
