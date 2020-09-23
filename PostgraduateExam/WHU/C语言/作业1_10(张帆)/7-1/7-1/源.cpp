#include<stdio.h>
#include<stdlib.h>

int main()
{
	int n;
	int a[32];
	int s, i;

	while (1)
	{
		scanf_s("%d", &s);
		int k = 0;
		if (s == 0)
		{
			printf("0\n");
			continue;
		}
		if (s == 1)
		{
			printf("1\n");
			continue;
		}
		for (i = 0; s != 0; i++)
		{
			a[i] = s % 2;
			s = s / 2;
			k++;
		}
		while ((k))
		{
			k--;
			printf("%d", a[k]);

		}
		printf("\n");

	}
	system("pause");
}