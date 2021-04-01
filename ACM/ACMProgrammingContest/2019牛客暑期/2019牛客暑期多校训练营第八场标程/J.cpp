#include <cstdio>
#include <algorithm>
using namespace std;
#define L 10000000 + 5
#define N 3000 + 5
#define Mod 998244353

int l, d, m, ans, F[L], Sum[L], Fac[L], Inv[L], T[N], P[N], In[N], Dp[N][2];
bool Go[N][N], Flag[N];

inline int Inc(int u, int v)
{
	return u + v - (u + v >= Mod ? Mod : 0);
}

void Prepare()
{
	F[0] = Sum[0] = Fac[0] = Inv[0] = Inv[1] = 1;
	for (int i = 1; i <= l; i ++)
	{
		F[i] = i >= d ? Sum[i - d] : 0;
		Sum[i] = Inc(Sum[i - 1], F[i]);
	}
	for (int i = 1; i <= l; i ++)
		Fac[i] = 1LL * Fac[i - 1] * i % Mod;
	for (int i = 2; i <= l; i ++)
		Inv[i] = Mod - (1LL * Inv[Mod % i] * (Mod / i) % Mod);
	for (int i = 2; i <= l; i ++)
		Inv[i] = 1LL * Inv[i - 1] * Inv[i] % Mod;
}

inline int C(int u, int v)
{
	if (u < v || u < 0 || v < 0)
		return 0;
	return 1LL * Fac[u] * Inv[v] % Mod * Inv[u - v] % Mod;
}

int main()
{
	scanf("%d%d%d", &l, &d, &m);
	Prepare();
	for (int i = 1; i <= m; i ++)
		scanf("%d%d", T + i, P + i);
	for (int i = 0; i <= m; i ++)
		for (int j = 0; j <= m; j ++)
			if (P[i] < P[j] && T[i] < T[j])
				Go[i][j] = true, In[j] ++;
	Dp[0][0] = 1;
	for (int t = 0; t <= m; t ++)
	{
		int id = -1;
		for (int i = 0; id == -1 && i <= m; i ++)
			if (In[i] == 0 && !Flag[i])
				id = i;
		Flag[id] = true;
		ans = (1LL * Dp[id][0] * F[l - P[id]] + Mod - (1LL * Dp[id][1] * F[l - P[id]] % Mod) + ans) % Mod;
		for (int i = 0; i <= m; i ++)
			if (Go[id][i])
			{
				if (P[i] - P[id] >= 1LL * d * (T[i] - T[id]))
				{
					int tmp = C(P[i] - P[id] - (d - 1) * (T[i] - T[id]) - 1, T[i] - T[id] - 1);
					Dp[i][0] = (1LL * Dp[id][1] * tmp + Dp[i][0]) % Mod;
					Dp[i][1] = (1LL * Dp[id][0] * tmp + Dp[i][1]) % Mod;
				}
				In[i] --;
			}
	}
	printf("%d\n", ans);
	return 0;
}
