#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
/*
这个真不会............

而且这个题的正误应该只能通过源代码吧99999
*/
double cubie(int n)
{
	return n*n*n*exp(n*sin(n));
}

int main()
{
	FILE *fr = NULL;
	fr = fopen("unix", "w+");
	if (fr == NULL)
	{
		printf("文件不存在\n");
		system("pause");
		exit(1);
	}

	FILE *pp = fopen("dos", "w+");
	int n;
	while (!feof(pp))
	{
		fscanf(pp, "%d", &n);
		if ((n<1) || (n>20))
		{
			fprintf(fr, "%s", "数字不合要求：");
			fprintf(fr, "%d", n);
		}
		else
		{
			fprintf(fr, "%lf", cubie(n));
		}
	}
	system("pause");
}