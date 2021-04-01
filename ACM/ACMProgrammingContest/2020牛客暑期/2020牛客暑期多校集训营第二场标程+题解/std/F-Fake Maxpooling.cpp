#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 5000 + 5

int n, m, k, A[N][N], B[N][N];
LL ans;

void Handle(int n, int m)
{
	static int q[N];
	for (int i = 1; i <= n; i ++)
	{
		int l = 1, r = 0;
		for (int j = 1; j < k; j ++)
		{
			for (; l <= r && A[i][q[r]] <= A[i][j]; r --) ;
			q[++ r] = j;
		}
		for (int j = k; j <= m; j ++)
		{
			for (; l <= r && q[l] + k <= j; l ++) ;
			for (; l <= r && A[i][q[r]] <= A[i][j]; r --) ;
			q[++ r] = j;
			B[j - k + 1][i] = A[i][q[l]];
		}
	}
}

int main()
{
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			if (!A[i][j])
				for (int k = 1; k * i <= n && k * j <= m; k ++)
					A[k * i][k * j] = k;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			A[i][j] = i * j / A[i][j];
	Handle(n, m);
	for (int i = 1; i <= m - k + 1; i ++)
		for (int j = 1; j <= n; j ++)
			A[i][j] = B[i][j];
	Handle(m - k + 1, n);
	for (int i = 1; i <= n - k + 1; i ++)
		for (int j = 1; j <= m - k + 1; j ++)
			ans += B[i][j];
	printf("%lld\n", ans);
	return 0;
}
