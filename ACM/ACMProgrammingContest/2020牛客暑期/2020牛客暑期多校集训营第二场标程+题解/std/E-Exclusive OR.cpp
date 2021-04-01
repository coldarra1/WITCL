#include <cstdio>
#include <algorithm>
using namespace std;
#define N 200000 + 5
#define LOGW 18
#define W (1 << LOGW)
#define Mod 998244353
#define Inv2 499122177

int n, A[N], T[W], CT[W], Ans[N];

inline int Inc(int u, int v)
{
	return u >= (Mod - v) ? u - (Mod - v) : u + v;
}

void FWT(int *p)
{
	for (int k = 1; k < W; k <<= 1)
		for (int i = 0; i < W; i ++)
			if ((i & k) == 0)
			{
				int u = Inc(p[i], p[i | k]);
				int v = Inc(p[i], Mod - p[i | k]);
				p[i] = u, p[i | k] = v;
			}
}

void NFWT(int *p)
{
	for (int k = W / 2; k; k >>= 1)
		for (int i = 0; i < W; i ++)
			if ((i & k) == 0)
			{
				int u = 1LL * Inc(p[i], p[i | k]) * Inv2 % Mod;
				int v = 1LL * Inc(p[i], Mod - p[i | k]) * Inv2 % Mod;
				p[i] = u, p[i | k] = v;
			}
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d", A + i);
	CT[0] = 1;
	for (int i = 1; i <= n; i ++)
		T[A[i]] = 1;
	FWT(CT), FWT(T);
	int lim = min(LOGW + 1, n);
	for (int i = 1; i <= lim; i ++)
	{
		for (int j = 0; j < W; j ++)
			CT[j] = 1LL * CT[j] * T[j] % Mod;
		NFWT(CT);
		int &mx = Ans[i];
		mx = -1;
		for (int j = W - 1; j >= 0 && (mx == -1); j --)
		{
			if (CT[j])
				mx = j;
			CT[j] = CT[j] ? 1 : 0;
		}
		FWT(CT);
	}
	for (int i = lim + 1; i <= n; i ++)
		Ans[i] = Ans[i - 2];
	for (int i = 1; i <= n; i ++)
		printf("%d%c", Ans[i], i == n ? '\n' : ' ');
	return 0;
}
