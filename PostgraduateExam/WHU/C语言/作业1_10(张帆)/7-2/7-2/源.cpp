#include<stdlib.h>
#include<stdio.h>

int main()
{
	int n;
	int a[32];
	int s, i;
	int m;
	while (1)
	{
		printf("输入数值与进制\n");
		scanf_s("%d", &s);
		scanf_s("%d", &m);
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
		printf("\n");
		system("pause");
		system("cls");
	}
	
}