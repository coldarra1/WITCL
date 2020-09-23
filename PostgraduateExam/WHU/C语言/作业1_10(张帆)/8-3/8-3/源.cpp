#include<stdio.h>
#include<stdlib.h>
/*
OJ又没有过？？？
*/

int main()
{
	int x, y;
	printf("输入矩阵的行与列数\n");
	while (scanf_s("%d%d", &x, &y))
	{
		printf("输入矩阵元素\n");
		int **matrix = (int **)malloc(sizeof(int *) * x);
		for (int i = 0; i < x; i++)
		{
			*(matrix + i) = (int *)malloc(sizeof(int) * y);
			for (int k = 0; k < y; k++)
			{
				scanf_s("%d", (*(matrix + i) + k));
			}
		}
		printf("转置后的矩阵为\n");

		for (int i = 0; i < y; i++)
		{
			for (int k = 0; k < x; k++)
			{
				printf("%d ", *(*(matrix + k) + i));
			}
			printf("\n");
		}
	}

	system("pause");

}