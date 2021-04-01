#include <cstdio>
#include <algorithm>
using namespace std;
#define N 1024 + 5

int n, A[N][N];

void Solve(int x)
{
	if (x == 1)
	{
		A[1][1] = 1;
		return ;
	}
	int t = x / 2;
	Solve(t);
	for (int i = 1; i <= t; i ++)
		for (int j = 1; j <= t; j ++)
		{
			A[i + t][j] = A[i][j + t] = A[i][j];
			A[i + t][j + t] = -A[i][j];
		}
}

int main()
{
	scanf("%d", &n);
	Solve(n);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= n; j ++)
			printf("%d%c", A[i][j], j == n ? '\n' : ' ');
	return 0;
}
