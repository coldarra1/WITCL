#include<stdio.h>
#include<stdlib.h>

struct qq
{
	int a;
	struct qq *next;
};

struct qq* creat()
{
	struct qq *head, *first, *last;
	head = (struct qq*)malloc(sizeof(struct qq));
	first = last = head;
	printf("输入-1结束\n");
	int n;
	scanf_s("%d", &n);
	while ((n!=-1))
	{
		first= (struct qq*)malloc(sizeof(struct qq));
		last->a = n;
		last->next = first;
		last = first;
		first->next = NULL;
		scanf_s("%d", &n);
	}
	return head;
}

struct qq* hebing(struct qq* one, struct qq* two)
{
	struct qq* p = one;
	while ((one->next)!=NULL)
	{
		one = (one->next);
	}
	one->a = two->a;
	one->next =two->next;
	return p;
}

int main()
{
	printf("请先创建两个新链表\n");
	struct qq *one, *two;
	one = creat();
	two = creat();
	printf("合并两个链表\n");
	one = hebing(one, two);
	while ((one->next)!=NULL)
	{
		printf("%d\n", one->a);
		one = one->next;
	}
	system("pause");
}