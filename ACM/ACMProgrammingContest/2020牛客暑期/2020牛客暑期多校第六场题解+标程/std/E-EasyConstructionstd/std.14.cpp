#include <cstdio>

int n, k;

int main()
{
	scanf("%d%d", &n, &k);
	if (k != (n * (n - 1) / 2) % n)
		puts("-1");
	else
	{
		printf("%d", n);
		if ((n & 1) == 0)
			printf(" %d", n / 2);
		for (int i = 1; i * 2 < n; i ++)
			printf(" %d %d", i, n - i);
		puts("");
	}
	return 0;
}
