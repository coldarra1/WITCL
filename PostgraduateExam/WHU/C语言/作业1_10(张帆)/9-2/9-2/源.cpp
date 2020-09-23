#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

/*结构体定义变量*/
typedef struct student 
{
	int num;
	double GPA;

}STU; 

 int avg(student *p1, int n)
{
	double sum = 0;
	student *pp = p1;
	for (int k = 0; k < n; k++)
	{
		sum = sum + (p1->GPA);
		p1++;
	}
	sum = sum / (double)n;
	printf("平均分:%lf\n", sum);
	int w=0;
	p1 = pp;
	printf("85分以上的学生\n");
	for (int k = 0; k <n; k++)
	{
		if ((pp->GPA)>85)
		{
			printf("学号：%d\t分数：%lf\n", pp->num, pp->GPA);
			w++;
		}
		pp++;
	}
	return w;
}

int main()
{
	STU a[10] = { 0 };
	int n;
	printf("请输入学生数目\n");
	scanf_s("%d", &n);
	printf("请输入ID与成绩\n");
	for (int i = 0; i <n; i++)
	{
		scanf_s("%d", &a[i].num);
		scanf_s("%lf", &a[i].GPA);
	}

	student *p, *p1;
	p = p1 = a;

	printf("85分以上的学生：%d", avg(p1, n));
	system("pause");
}