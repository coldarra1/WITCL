#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int sum = 99999;
int n;
void min(int *p)
{
	n--;
	if (n >= 0)
	{
		if (*p<sum)
		{
			sum = *p;
		}
		p++;
		min(p);

	}
	else
	{
		printf("%d", sum);
	}
}

int main()
{
	printf("请输入数组大小\n");
	while (scanf_s("%d", &n))
	{
		if (n==1)
		{
			break;

		}
		int a[108];
		printf("输入数组元素\n");
		for (int i = 0; i < n; i++)
		{
			scanf_s("%d",&a[i]);
		}
		int *p = a;
		min(p);
		system("pause");
	}
}