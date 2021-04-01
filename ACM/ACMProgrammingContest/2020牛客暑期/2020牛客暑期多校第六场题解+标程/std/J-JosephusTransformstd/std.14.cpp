#include <cstdio>
#include <algorithm>
using namespace std;
#define N 1000 + 5

int n, m, T[N];

struct Transform
{
	int sz, num[N];
	
	Transform() {}
	Transform(int sz) : sz(sz)
	{
		for (int i = 1; i <= sz; i ++)
			num[i] = i;
	}
	void out() const
	{
		for (int i = 1; i <= sz; i ++)
			printf("%d%c", num[i], i == sz ? '\n' : ' ');
	}
}P;

void Modify(int x, int k)
{
	for (; x <= n; x += (x & -x))
		T[x] += k;
}

int Calc(int x)
{
	int res = 0;
	for (; x; x -= (x & -x))
		res += T[x];
	return res;
}

int GetPos(int rank)
{
	int mid, x = 0;
	for (mid = 1; mid <= n && T[mid] < rank; mid <<= 1) ;
	for (mid >>= 1; mid; mid >>= 1)
		if (x + mid <= n && T[x + mid] < rank)
		{
			x += mid;
			rank -= T[x];
		}
	return x + 1;
}

Transform GetTrans(int k)
{
	Transform res;
	res.sz = n;
	for (int i = 1; i <= n; i ++)
		T[i] = i & -i;
	for (int i = 1, last = 0; i <= n; i ++)
	{
		int tot = n - i + 1;
		int pre = Calc(last);
		int rank = (pre + k - 1) % tot + 1;
		int pos = GetPos(rank);
		Modify(pos, -1);
		last = res.num[i] = pos;
	}
	return res;
	
}

Transform Union(const Transform &lhs, const Transform &rhs)
{
	Transform res;
	res.sz = lhs.sz;
	for (int i = 1; i <= res.sz; i ++)
		res.num[i] = rhs.num[lhs.num[i]];
	return res;
}

Transform Power(const Transform &base, int k)
{
	Transform res(base.sz);
	for (Transform u = base; k; k >>= 1)
	{
		if (k & 1)
			res = Union(res, u);
		u = Union(u, u);
	}
	return res;
}

int main()
{
	scanf("%d%d", &n, &m);
	P = Transform(n);
	for (int i = 1, k, x; i <= m; i ++)
	{
		scanf("%d%d", &k, &x);
		Transform trans = GetTrans(k);
		P = Union(P, Power(trans, x));
	}
	P.out();
	return 0;
}
