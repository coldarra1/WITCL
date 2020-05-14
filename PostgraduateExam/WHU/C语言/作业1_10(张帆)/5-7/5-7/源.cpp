#include<stdio.h>
#include<stdlib.h>

int n(int s, int m)
{
	int a[32];
	int i;
	int k = 0;
	if (s<m)
	{
		printf("%d", s);
	}
	for (i = 0; s != 0; i++)
	{
		a[i] = s %m;
		s = s / m;
		k++;
	}
	while ((k))
	{
		k--;
		if (a[k]>9)
		{
			switch (a[k])
			{
			case 10:
				printf("A");
				break;
			case 11:
				printf("B");
				break;
			case 12:
				printf("C");
				break;
			case 13:
				printf("D");
				break;
			case 14:
				printf("E");
				break;
			case 15:
				printf("F");
				break;
			case 16:
				printf("G");
				break;
			}

		}
		else
		{
			printf("%d", a[k]);
		}

	}

	return 0;
}

int main()
{
	int s, m;
	printf("请输入数与进制\n");			//s为数，m为进制	
	scanf_s("%d%d", &s, &m);
	n(s, m);
	printf("\n");
	system("pause");
}