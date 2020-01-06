#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	printf("关键词统计\n");
	int n, sum = 0;
	char a[11][11];
	char str[1008];
	printf("请输入关键词\n");
	for (int i = 0; i <10; i++)
	{
		scanf("%s", &a[i]);	
	}
	printf("请输入字符串\n");
	scanf("%s", &str);
	
	int l = strlen(str);
	for (int i = 0; i <10; i++)
	{
		sum = 0;
		int len = strlen(a[i]);
		for (int x = 0, y = 0; x<l; x++)        //x为原字符串
		{
			char w = a[i][y];
			char e = str[x];
			if (a[i][y] == str[x])
			{
				if (y == (len - 1))
				{
					y = 0;
					sum++;
				}
				else
				{
					y++;
				}
			}
			else
			{
				x = x - y;
				y = 0;
			}
		}
		printf("%s\t", a[i]);
		printf("%d\n", sum);
		
	}

	system("pause");

}