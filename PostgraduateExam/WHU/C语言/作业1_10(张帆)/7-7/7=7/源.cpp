#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int findx(int d[], int n, int x)
{
	int i;
	int sum = 0;
	for (i = 0; i<n; i++)
	{
		if (d[i] == x)
		{
			sum++;
			break;
		}

	}
	if (sum == 0)
	{
		return -1;
	}
	else
	{
		return i;
	}

}

int main()
{
	int n;
	printf("输入数组大小\n");
	scanf_s("%d", &n);
	int a[108];
	printf("输入数组元素\n");
	for (int i = 0; i <n; i++)
	{
		scanf_s("%d", &a[i]);
	}
	printf("输入关键字\n");
	int q;
	scanf_s("%d", &q);
	printf("%d", findx(a, n, q));

	system("pause");

}