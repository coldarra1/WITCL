#include <bitset>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 150000 + 5
#define M 40000 + 5

int n, m, ans, A[N], B[M], Ord[M];
bitset<M> cur, Bs[M];

int GetRank(int x)
{
	int l = 0, r = m;
	while (l < r)
	{
		int mid = l + r >> 1;
		if (x < B[Ord[mid]])
			r = mid;
		else l = mid + 1;
	}
	return l;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i ++)
		scanf("%d", A + i);
	for (int i = 0; i < m; i ++)
	{
		scanf("%d", B + i);
		Ord[i] = i;
	}
	sort(Ord, Ord + m, [](int u, int v) {
		return B[u] < B[v];
	});
	for (int i = 1; i <= m; i ++)
	{
		Bs[i] = Bs[i - 1];
		Bs[i].set(Ord[i - 1]);
	}
	for (int i = n - 1; i >= 0; i --)
	{
		cur >>= 1;
		cur &= Bs[GetRank(A[i])];
		if (A[i] >= B[m - 1])
			cur.set(m - 1);
		ans += cur[0];
	}
	printf("%d\n", ans);
	return 0;
}
