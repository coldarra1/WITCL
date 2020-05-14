#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char a[1008];
int substitute(char str[], char oldchar, char newchar)
{

	int len, n = 0;
	len = strlen(a);
	for (int i = 0; i < len; i++)
	{
		if (a[i] == oldchar)
		{
			a[i] = newchar;
			n++;
		}
	}
	printf("%d ", n);
	printf("%s\n", a);
	return 0;
}

int main()
{
	char b, c;
	printf("ÇëÊäÈë:×Ö·û´®£¬Ô­×Ö·û£¬Ìæ»»×Ö·û\n");
	scanf("%s %c %c",a,&b,&c);
	substitute(a, b, c);
	system("pause");
}