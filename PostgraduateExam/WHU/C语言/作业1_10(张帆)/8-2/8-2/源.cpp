#include<stdio.h>
#include<stdlib.h>
/*





*/

int main()
{
	while (1)
	{
		int a[2];
		printf("请输入三个整数\n");
		scanf_s("%d%d%d", &a[0], &a[1], &a[2]);
		int b[2];
		b[0] = a[0];
		b[1] = a[1];
		b[2] = a[2];
		if (b[0] > b[1])
		{
			int q;
			q = b[0];
			b[0] = b[1];
			b[1] = q;
		}
		if (b[1] > b[2])
		{
			int q;
			q = b[1];
			b[1] = b[2];
			b[2] = q;
		}
		if (b[0]>b[1])
		{
			int q;
			q = b[0];
			b[0] = b[1];
			b[1] = q;
		}

		printf("%d\t%d\t%d", b[0], b[1], b[2]);
	}
}