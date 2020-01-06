#include <stdio.h>  
#include <stdlib.h>  

int main()
{
	int i, j, k;		//i,j,k分别对应a,b,c的对手 
	printf("所有结果\n");
	for (i = 'x'; i <= 'z'; i++)
	{
		for (j = 'x'; j <= 'z'; j++)
		{
			if (j != i)
			{
				for (k = 'x'; k < 'z'; k++)
				{
					if (k != i&&k != j)
					{
						printf("a对战%c  b对战%c  c对战%c\n", i, j, k);
					}
				}
			}
		}
	}

	printf("名单\n");
	for (i = 'x'; i <= 'z'; i++)
	{
		for (j = 'x'; j <= 'z'; j++)
		{
			if (j != i)
			{
				for (k = 'x'; k < 'z'; k++)
				{
					if (k != i&&k != j)
					{
						if (i != 'x'&&k != 'x'&&k != 'z')
						{
							printf("a对战%c  b对战%c  c对战%c", i, j, k);
						}
					}
				}
			}
		}
	}

	system("pause");
}