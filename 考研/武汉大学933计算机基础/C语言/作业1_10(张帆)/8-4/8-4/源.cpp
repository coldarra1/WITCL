#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

/*结构体定义变量*/
struct student                                                     
{
	int num;
	double GPA;

}a[10];

student*max(student *p1, int n)
{
	student *pp = p1;
	for (int k = 1; k <n; k++)
	{
		if ((pp->GPA)<((p1 + 1)->GPA))
		{
			pp = (p1+1);
		}
		p1++;
	}
	return pp;
}

student*min(student *p1, int n)
{
	student *pp = p1;
	for (int k = 1; k <n; k++)
	{
		if ((pp->GPA)>((p1 + 1)->GPA))
		{
			pp = (p1 + 1);
		}
		p1++;
	}
	return pp;
}
student*avg(student *p1, int n)
{
	double sum = 0;
	student *pp = p1;
	for (int k = 0; k < n; k++)
	{
		sum = sum + (p1->GPA);
		p1++;
	}
	sum = sum /(double)n;
	printf("平均分%lf", sum);
	double cha;
	p1 = pp;
	cha = fabs((p1->GPA) - sum);
	for (int k = 0; k <n; k++)
	{
		if (fabs(((pp->GPA)-sum))<cha)
		{
			cha = ((pp->GPA) - sum);
			p1 = pp;
		}
		pp++;
	}
	return p1;
}

int main()
{
	int n;
	printf("请输入学生数目\n");
	scanf_s("%d", &n);
	printf("请输入ID与成绩\n");
	for (int  i = 0; i <n; i++)
	{
		scanf_s("%d", &a[i].num);
		scanf_s("%lf", &a[i].GPA);
	}
	student *p,*p1;
	p=p1=a;
	p1 = max(p, n);

	printf("最佳学生：%d\t%lf\t", p1->num,p1->GPA);
	printf("最高分下标：%d\n",p1-p);
	
	p1 = min(p, n);
	printf("最差学生：%d\t%lf\t", p1->num, p1->GPA);
	printf("最低分下标：%d\n", p1 - p);

	p1 = avg(p, n);
	printf("平均学生：%d\t%lf\t", p1->num, p1->GPA);
	printf("平均学生下标：%d\n", p1 - p);


	system("pause");
}