#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double cubie(int n)
{
	return n*n*n*exp(n*sin(n));
}

int main()
{
	FILE *fr=NULL;
	fr = fopen("experience.out", "rb+");
	if (fr==NULL)
	{
		printf("文件不存在\n");
		system("pause");
		exit(1);
	}

	/*while (k--)
	{
		int q = rand() % 30;					//向文件写入k个随机数
		fprintf(fr, "%d ", q);
	}*/

	FILE *pp = fopen("experience.in", "rb+");
	int n;
	while (!feof(pp))
	{
		fscanf(pp, "%d", &n);
		if ((n<1)||(n>20))
		{
			fprintf(fr, "%s", "数字不合要求：");
			fprintf(fr, "%d",n);
		}
		else
		{
			fprintf(fr, "%lf",cubie(n));
		}
	}
	system("pause");
}