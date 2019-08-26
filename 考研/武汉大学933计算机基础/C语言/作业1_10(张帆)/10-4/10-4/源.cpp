#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*结构体定义变量*/
struct student
{
	char name[10];
	char  author[20];
	char pulish[30];
	char price[20];
	char num[10];
	char lei[20];
}book;

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
		printf("请输入书籍的名称:\t");
		getchar();
		gets_s(book.name);

		printf("作者:\t");
		gets_s(book.author);

		printf("出版社:\t");
		gets_s(book.pulish);
		
		printf("价格:\t");
		gets_s(book.price);
		
		printf("库存数目:\t");
		gets_s(book.num);
		
		printf("种类:\t");
		gets_s(book.lei);
		if (fwrite(&book, sizeof(struct student), 1, fp) != 1)
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
	printf("请输入要查询的方式\n\t1.作者 2.书名:\n\t请选择 1 or 2 \t");
	scanf("%d", &a);
	if (a == 1)
	{
		printf("请输入作者:\t");
		getchar();
		gets_s(ch);
		while (fread(&book, sizeof(struct student), 1, fp) == 1)
			if (strcmp(book.name, ch) == 0)
			{
				b = 1;
				printf("书名\t作者\t出版社\t单价\t库存数目\t类别\n");
				printf("%s\t%s\t%s\t%s\t%s\t%s\n", book.name, book.author, book.pulish, book.price,book.num,book.lei);
			}
		if (b == 0) printf("input error!\n");
	}
	else if (a == 2)
	{
		printf("请输入书名:\t");
		getchar();
		gets_s(ch);
		while (fread(&book, sizeof(struct student), 1, fp) == 1)
			if (strcmp(book.name, ch) == 0)
			{
				b = 1;
				printf("书名\t作者\t出版社\t单价\t库存数目\t类别\n");
				printf("%s\t%s\t%s\t%s\t%s\t%s\n", book.name, book.author, book.pulish, book.price, book.num, book.lei);
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
		printf("请输入书籍的名称:\t");
		getchar();
		gets_s(book.name);

		printf("作者:\t");
		gets_s(book.author);

		printf("出版社:\t");
		gets_s(book.pulish);

		printf("价格:\t");
		gets_s(book.price);

		printf("库存数目:\t");
		gets_s(book.num);

		printf("种类:\t");
		gets_s(book.lei);
		if (fwrite(&book, sizeof(struct student), 1, fp) != 1)
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

/*输出文档中的信息*/
void display()
{
	FILE *fp;
	if ((fp = fopen("zf.dat", "rb")) == NULL)
	{
		printf("文件不存在\n");
		return;
	}
	printf("书名\t作者\t出版社\t单价\t库存数目\t类别\n");
	while (fread(&book, sizeof(struct student), 1, fp) == 1)
	{
		printf("%s\t%s\t%s\t%s\t%s\t%s\n", book.name, book.author, book.pulish, book.price, book.num, book.lei);
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
		printf("请输入要删除的书名:\t");
		scanf("%s", ch);
		n++;
		while (fread(&book, sizeof(struct student), 1, fp) == 1)
		{
			if ((strcmp(book.name, ch) == 0))
			{
				b = 1;
				printf("书名\t作者\t出版社\t单价\t库存数目\t类别\n");
				printf("%s\t%s\t%s\t%s\t%s\t%s\n", book.name, book.author, book.pulish, book.price, book.num, book.lei);
			}
			else if (strcmp(book.name, ch) != 0)
				fwrite(&book, sizeof(struct student), 1, fp2);
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


/*菜单*/
void interface()
{
	int choose;
	printf("\t\t\t******图书管理系统**********\n");
	printf("\t\t\t****1.录入		****\n");
	printf("\t\t\t****2.显示		****\n");
	printf("\t\t\t****3.查询		****\n");
	printf("\t\t\t****4.添加		****\n");
	printf("\t\t\t****5.修改		****\n");
	printf("\t\t\t****6.删除		****\n");
	printf("\t\t\t****0.帮助		****\n");
	printf("\t\t\t****************************\n");
	printf("\t\t\t*本程序没有丝毫健壮性，请小心操作*\n");
	printf("请选择 0--6:\n");
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