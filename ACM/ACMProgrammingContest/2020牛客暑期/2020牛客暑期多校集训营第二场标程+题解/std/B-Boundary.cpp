#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef __int128_t LLL;
#define N 2000 + 5

int n, ans = 1, X[N], Y[N];

struct Frac
{
	LL fz, fm;
	Frac() : Frac(0, 1){}
	Frac(LL fz, LL fm) : fz(fz), fm(fm) {}
	bool operator < (const Frac &rhs)
	{
		return (LLL) fz * rhs.fm < (LLL) fm * rhs.fz;
	}
	bool operator == (const Frac &rhs)
	{
		return (LLL) fz * rhs.fm == (LLL) fm * rhs.fz;
	}
}A[N];

int Cross(int lhs, int rhs)
{
	return X[lhs] * Y[rhs] - X[rhs] * Y[lhs];
}

int Dot(int lhs, int rhs)
{
	return X[lhs] * X[rhs] + Y[lhs] * Y[rhs];
}

int Dis2(int lhs, int rhs)
{
	int dx = X[lhs] - X[rhs], dy = Y[lhs] - Y[rhs];
	return dx * dx + dy * dy;
}

int Sgn(int x)
{
	if (x > 0) return 1;
	if (x < 0) return -1;
	return 0;
}

Frac GetCosAngle2(int i, int j)
{
	int a2 = Dis2(0, i), b2 = Dis2(i, j), c2 = Dis2(0, j);
	int sgn = Sgn(b2 + c2 - a2);
	return Frac(1LL * sgn * (b2 + c2 - a2) * (b2 + c2 - a2), 4LL * b2 * c2);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d%d", X + i, Y + i);
	for (int i = 1; i <= n; i ++)
	{
		int cnt = 0;
		for (int j = 1; j <= n; j ++)
			if (Cross(i, j) > 0)
				A[++ cnt] = GetCosAngle2(i, j);
		sort(A + 1, A + cnt + 1);
		for (int l = 1, r; l <= cnt; l = r)
		{
			for (r = l; A[l] == A[r] && r <= cnt; r ++) ;
			ans = max(ans, r - l + 1);
		}
	}
	printf("%d\n", ans);
	return 0;
}
