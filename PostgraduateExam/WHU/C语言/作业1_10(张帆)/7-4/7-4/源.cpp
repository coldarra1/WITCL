#include<stdio.h>
#include<stdlib.h>

int main()
{
	printf("输入10个整数\n");
	int a[16];
	scanf_s("%d", &a[0]);
	for (int  i = 1; i <10; i++)
	{
		int q;
		scanf_s("%d",&q);
		for (int k = 0; k < i; k++)
		{
			if (q>=a[i-1])
			{
				a[i] = q;
				break;
			}
			if (q<a[k])
			{
				int p = i;
				while ((p--)&&(p>=k))
				{
					a[p+1] = a[p];
				}
				a[k] = q;
				break;
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d\n", a[i]);
	}
	system("pause");
}