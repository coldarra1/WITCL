#include<stdio.h>
#include<stdlib.h>

int max(int *p)
{
	int q=*p;
	while (*p!=-1)
	{
		if (q<*(p+1))
		{
			q = *(p + 1);
		}
		p = p + 1;
	}
	return q;
}
int min(int *p)
{
	int q = *p;
	while (*p != -1)
	{
		if ((q>*(p + 1))&&(*(p+1)!=-1))
		{
			q = *(p + 1);
		}
		p = p + 1;
	}
	return q;
}

int main()
{
	int a[10086];
	int i = 0;
	scanf_s("%d", &a[i]);
	while (a[i]!=-1)
	{
		i++;
		scanf_s("%d", &a[i]);		
	}
	int *p;
	p = a;
	printf("最大值%d\n", max(p));
	p = a;
	printf("最小值%d", min(p));
	system("pause");
}