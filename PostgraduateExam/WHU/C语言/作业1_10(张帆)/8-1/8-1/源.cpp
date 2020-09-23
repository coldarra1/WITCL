#include<stdio.h>
#include<stdlib.h>


int main()
{
	printf("÷∏’Î\n");
	int ar[10] = {11,13,15,17,19,21,23,25,27,29};
	int *pt;
	pt = ar;
	printf("%p\n", &ar[0]);
	printf("%p\n", &pt);
	printf("%d\n", *pt);
	printf("%d\n", *pt + 3);
	printf("%d\n", pt[3]);
	printf("%p\n", &*pt);
	printf("%p\n", *&pt);
	printf("%d\n", *(pt + 3));
	printf("%d\n", *pt++);
	printf("%d\n", *(pt++));
	printf("%d\n", (*pt)++);




	system("pause");
}