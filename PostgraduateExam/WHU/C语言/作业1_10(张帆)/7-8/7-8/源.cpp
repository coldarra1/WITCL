#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a[20086];
int binary_search(int d[], int s, int e, int q)
{
	int t;
	if ((q<a[s]) || (q >= a[e]))
	{
		return -1;
	}
	while ((e - s)>1)
	{
		t = (e + s) / 2;
		if (a[t] == q)
		{
			return t;
		}
		if (a[t]>q)
		{
			s = t;
		}
		if (a[t]<q)
		{
			e = t;
		}
	}
	return -1;
}

int main()
{

	int n;
	printf("输入数组大小\n");
	scanf_s("%d", &n);
	printf("输入数组元素\n");
	for (int i = 0; i <n; i++)
	{
		scanf_s("%d", &a[i]);
		
	}
	
	printf("输入查找的起始下标与终止下标与查找的数\n");
	int s, e, q;
	scanf_s("%d%d%d", &s, &e, &q);
	
	printf("%d", binary_search(a, s, e, q));
	
	system("pause");
}