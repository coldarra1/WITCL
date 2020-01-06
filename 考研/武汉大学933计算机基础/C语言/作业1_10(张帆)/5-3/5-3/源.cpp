#include<stdio.h>
#include<stdlib.h>

int flip()
{
	int a;
	a = rand() % 2;
	return a;
}

int main()
{
	int n = 100, a;
	int ji = 0, ou = 0;
	while (n--)
	{
		a = flip();
		if (a == 1)
		{
			printf("1 ");
			ou++;
		}
		else
		{
			printf("0 ");
			ji++;
		}
	}
	printf("\n");
	printf("%d %d\n", ou, ji);
	system("pause");


}