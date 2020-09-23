#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n =10;
	int sum = 1;
	while (n--)
	{
		sum++;
		sum = sum * 2;
	}
	printf("%d", sum);
	system("pause");
	
}