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
	int n;
	printf("请输入链表(长度大于3)以-1结束\n");
	scanf_s("%d", &n);
	while (n!=-1)											//头节点放了数据
	{
		first = (struct qq*)malloc(sizeof(struct qq));
		last->a = n;
		last->next = first;
		last = first;
		first->next = NULL;
		scanf_s("%d", &n);
	}
	return head;
}

struct qq* nixu(struct qq* one)
{
	struct qq* first= one;
	struct qq* last=one;
	first = first->next;
	last = first;
	first = first->next;
	one->next = NULL;
	while ((first->next) != NULL)
	{
		last->next = one;
		one = last;
		last = first;
		first = first->next;
	}
	last->next = one;
	first->next = last;
	return first;
}

int main()
{
	printf("请先创建一个新链表\n");
	struct qq *one, *two;
	one = creat();
	printf("将链表逆序\n");
	one = nixu(one);
	printf("打印逆序链表\n");
	while ((one->next) != NULL)					//逆序后头结点无数据
	{
		one = one->next;
		printf("%d\n", one->a);	
	}
	system("pause");
}