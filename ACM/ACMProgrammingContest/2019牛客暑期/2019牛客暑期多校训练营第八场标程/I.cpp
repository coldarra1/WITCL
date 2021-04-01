#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 300000 + 5
#define M 1048576 + 5
#define mp make_pair
#define ls(x) x << 1
#define rs(x) x << 1 | 1

int n, m, q, sz, L[N], R[N], Fa[N], Le[N], Ri[N], Del[M];
LL Sum[M], Ans[N];
vector<int> Vec[N];
bool Flag[N];

struct Operation
{
	int x, op, l, r, id, a;
	Operation() {}
	Operation(int x, int op, int l, int r, int id, int a)
		: x(x), op(op), l(l), r(r), id(id), a(a) {
	}
	bool operator < (const Operation &obj) const
	{
		return mp(x, op) < mp(obj.x, obj.op);
	}
}Op[N << 2];

void dfs(int st)
{
	int ord = 0;
	vector<int> Sta;
	Sta.push_back(st);
	while (!Sta.empty())
	{
		int z = Sta.back();
		if (!Le[z]) Le[z] = ++ ord;
		for (; !Vec[z].empty() && Vec[z].back() == Fa[z]; Vec[z].pop_back()) ;
		if (!Vec[z].empty())
		{
			int d = Vec[z].back();
			Fa[d] = z, Sta.push_back(d);
			Vec[z].pop_back();
		}
		else Ri[z] = ord, Sta.pop_back();
	}
}

inline void apply(int x, int l, int r, int k)
{
	Del[x] += k, Sum[x] += 1LL * (r - l + 1) * k;
}

inline void push(int x, int l, int r)
{
	if (Del[x])
	{
		int mid = l + r >> 1;
		apply(ls(x), l, mid, Del[x]);
		apply(rs(x), mid + 1, r, Del[x]);
		Del[x] = 0;
	}
}

void Modify(int x, int l, int r, int s, int t, int k)
{
	if (l == s && r == t)
	{
		apply(x, l, r, k);
		return ;
	}
	push(x, l, r);
	int mid = l + r >> 1;
	if (t <= mid)
		Modify(ls(x), l, mid, s, t, k);
	else if (s > mid)
		Modify(rs(x), mid + 1, r, s, t, k);
	else Modify(ls(x), l, mid, s, mid, k), Modify(rs(x), mid + 1, r, mid + 1, t, k);
	Sum[x] = Sum[ls(x)] + Sum[rs(x)];
}

LL Query(int x, int l, int r, int s, int t)
{
	if (l == s && r == t)
		return Sum[x];
	push(x, l, r);
	int mid = l + r >> 1;
	if (t <= mid)
		return Query(ls(x), l, mid, s, t);
	else if (s > mid)
		return Query(rs(x), mid + 1, r, s, t);
	else return Query(ls(x), l, mid, s, mid) + Query(rs(x), mid + 1, r, mid + 1, t);
}

int main()
{
	scanf("%d%d", &n, &m);
	L[1] = 1, R[1] = n, Flag[1] = true;
	for (int i = 1, u, v, l, r; i <= m; i ++)
	{
		scanf("%d%d%d%d", &u, &v, &l, &r);
		Flag[v] = true;
		Vec[u].push_back(v);
		L[v] = l, R[v] = r;
	}
	dfs(1);
	for (int i = 1; i <= m + 1; i ++)
		Op[++ sz] = Operation(Le[i], 0, L[i], R[i], 0, 1);
	scanf("%d", &q);
	for (int i = 1, u, l, r; i <= q; i ++)
	{
		scanf("%d%d%d", &u, &l, &r);
		Op[++ sz] = Operation(Le[u] - 1, 1, l, r, i, -1);
		Op[++ sz] = Operation(Ri[u], 1, l, r, i, 1);
	}
	sort(Op + 1, Op + sz + 1);
	for (int i = 1; i <= sz; i ++)
	{
		if (Op[i].op == 0)
			Modify(1, 1, n, Op[i].l, Op[i].r, Op[i].a);
		else Ans[Op[i].id] += Query(1, 1, n, Op[i].l, Op[i].r) * Op[i].a;
	}
	for (int i = 1; i <= q; i ++)
		printf("%lld\n", Ans[i]);
	return 0;
}
