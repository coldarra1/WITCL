#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*借用学生管理系统的菜单(^_^)
也算过关吧！*/

/*结构体定义变量*/
struct student
{
	char  num[20];
	char name[10];
	float GPA;
	int  many;

}stu;

/*帮助*/
void help()
{
	printf("******没有帮助********\n");
}

/*第一次输入信息并保存在文件中 */
void create()
{
	system("cls");
	char ch;
	FILE *fp;
	if ((fp = fopen("zf.dat", "wb+")) == NULL)
	{
		printf("文件不存在\n");
		exit(0);
	}
	//文件是否存在

	do
	{
		printf("请输入成绩的--编号:\t");
		getchar();
		gets_s(stu.num);
		printf("姓名:\t");
		gets_s(stu.name);
		printf("成绩:\t");
		scanf("%f", &stu.GPA);
		printf("学号:\t");
		scanf("%d", &stu.many);
		if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)
		{
			printf("文件不存在\n");
			exit(0);
		}

		printf("是否继续输入y or n ?\t");
		getchar();
		ch = getchar();
	} while (ch == 'y');
	fclose(fp);

}

/*查询*/
void find()
{
	int a, b = 0;
	char ch[20];
	FILE *fp;
	if ((fp = fopen("zf.dat", "rb")) == NULL)
	{
		printf("cannot open file\n");
		exit(0);
	}
	printf("请输入要查询的成绩的方式\n\t1.编号 2.姓名:\n\t请选择 1 or 2 \t");
	scanf("%d", &a);
	if (a == 1)
	{
		getchar();
		printf("请输入成绩的编号:\t");
		gets_s(ch);
		while (fread(&stu, sizeof(struct student), 1, fp) == 1)
			if (strcmp(stu.num, ch) == 0)
			{
				b = 1;
				printf("编号\t姓名\t成绩\t\t学号\n");
				printf("%s\t%s\t%.3f\t\t%d\n", stu.num, stu.name, stu.GPA, stu.many);
			}
		if (b == 0) printf("对不起！没有找到相关信息：\n");
	}
	else if (a == 2)
	{
		printf("请输入成绩的姓名:\t");
		getchar();
		gets_s(ch);
		while (fread(&stu, sizeof(struct student), 1, fp) == 1)
			if (strcmp(stu.name, ch) == 0)
			{
				b = 1;
				printf("编号\t姓名\t成绩\t\t学号\n");
				printf("%s\t%s\t%.3f\t\t%d\n", stu.num, stu.name, stu.GPA, stu.many);
			}
		if (b == 0) printf("input error!\n");
	}
	fclose(fp);
}

/*添加*/
void add()
{
	char ch;
	FILE *fp;
	if ((fp = fopen("zf.dat", "ab")) == NULL)
	{
		printf("文件不存在\n");
		exit(0);
	}

	do
	{
		printf("请输入要添加成绩的--编号:\t");
		getchar();
		gets_s(stu.num);
		printf("姓名:\t");
		gets_s(stu.name);
		printf("GPA:\t");
		scanf("%f", &stu.GPA);
		printf("学号:\t");
		scanf("%d", &stu.many);
		if (fwrite(&stu, sizeof(struct student), 1, fp) != 1)
		{
			printf("文件不存在\n");
			exit(0);
		}

		printf("是否继续输入y or n ?\t");
		getchar();
		ch = getchar();
	} while (ch == 'y' || ch == 'Y');
	fclose(fp);
}

/*输出文档中的信息*/
void display()
{
	FILE *fp;
	if ((fp = fopen("zf.dat", "rb")) == NULL)
	{
		printf("文件不存在\n");
		return;
	}
	printf("编号\t姓名\t成绩\t\t学号\n");
	while (fread(&stu, sizeof(struct student), 1, fp) == 1)
	{
		printf("%s\t%s\t%.3f\t\t%d\n", stu.num, stu.name, stu.GPA, stu.many);
	}
	fclose(fp);
}

/*删除 */
void shanchu()
{
	FILE *fp2;
	int a, b = 0, c = 0, n = 0;
	char ch[20], ck;
	FILE *fp;

	do {
		if ((fp = fopen("zf.dat", "rb")) == NULL)
		{
			printf("cannot open file\n");
			exit(0);
		}
		if ((fp2 = fopen("temp.dat", "wb")) == NULL)
		{
			printf("cannot open file\n");
			exit(0);
		}
		printf("请输入要删除成绩的编号:\t");
		scanf("%s", ch);
		n++;
		while (fread(&stu, sizeof(struct student), 1, fp) == 1)
		{
			if ((strcmp(stu.num, ch) == 0))
			{
				b = 1;
				printf("编号\t姓名\t成绩\t\t学号\n");
				printf("%s\t%s\t%.3f\t\t%d\n", stu.num, stu.name, stu.GPA, stu.many);
			}
			else if (strcmp(stu.num, ch) != 0)
				fwrite(&stu, sizeof(struct student), 1, fp2);
		}
		if (b == 0)
		{
			printf("\t没有找到相关信息！\n");
			getchar();
		}
		rewind(fp);
		getchar();
		getchar();
		printf("删除成功！");
		getchar();
		printf("是否继续删除？enter 'y' or 'n' \t");
		ck = getchar();
		fclose(fp);
		fclose(fp2);
		remove("zf.dat");
		rename("temp.dat", "zf.dat");
	} while (ck == 'y');
	if (b != 0)
		printf("\t保存成功：\n");

}

/*修改*/
void change()
{
	shanchu();
	add();
}

/*排名*/
void paiming()
{



}

/*菜单*/
void interface()
{
	int choose;
	printf("\t\t\t******学生管理系统**********\n");
	printf("\t\t\t****1.录入		****\n");
	printf("\t\t\t****2.显示		****\n");
	printf("\t\t\t****3.查询		****\n");
	printf("\t\t\t****4.添加		****\n");
	printf("\t\t\t****5.修改		****\n");
	printf("\t\t\t****6.删除		****\n");
	printf("\t\t\t****0.帮助		****\n");
	printf("\t\t\t****************************\n");
	printf("请选择 0--7:\n");
	printf("请输入你的选择\n");
	scanf("%d", &choose);
	while (choose>7 || choose<0)
	{
		printf("输入有误，请重来\n");
		getchar();			//没有这个，输入错误会爆
		scanf("%d", &choose);
	}
	switch (choose)
	{

	case 0:
		help();
		break;
	case 1:
		create();
		break;
	case 2:
		display();
		break;
	case 3:
		find();
		break;
	case 4:
		add();
		break;
	case 5:
		change();
		break;
	case 6:
		shanchu();
		break;
	case 7:
		paiming();
		break;

	}
}

/*主函数*/
int main()
{
	while (1)
	{
		interface();
		system("pause");
		system("cls");
	}
}