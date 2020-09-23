#include<stdio.h>
#include<stdlib.h>

int fibonacci(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);

}

int main()
{
	int n = 100, sum1, sum2;
	printf(" ‰»În\n");
	scanf_s("%d", &sum1);
	sum2 = fibonacci(sum1);
	printf("%d\n", sum2);
	
	system("pause");
}
