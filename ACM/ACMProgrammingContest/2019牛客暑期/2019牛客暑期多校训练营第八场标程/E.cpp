#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define N 100000 + 5
#define M 524288 + 5
#define ls(x) x << 1
#define rs(x) x << 1 | 1

int n, m, sz, ans, T[N << 1], Fa[N], Height[N];
vector<pair<int, int>> Vec[M];

struct Edge
{
	int a, b, l, r;
	Edge() {}
	Edge(int a, int b, int l, int r) : a(a), b(b), l(l), r(r) {}
}E[N];

void Add(int x, int l, int r, int s, int t, int a, int b)
{
	if (l == s && r == t)
	{
		Vec[x].push_back(make_pair(a, b));
		return ;
	}
	int mid = l + r >> 1;
	if (t <= mid)
		Add(ls(x), l, mid, s, t, a, b);
	else if (s >= mid)	
		Add(rs(x), mid, r, s, t, a, b);
	else Add(ls(x), l, mid, s, mid, a, b), Add(rs(x), mid, r, mid, t, a, b);
}

int Find(int x)
{
	return x == Fa[x] ? x : Find(Fa[x]);
}

struct Record
{
	int u, v, h_v;
	Record(int u, int v, int h_v) : u(u), v(v), h_v(h_v) {}
};

void DFS(int x, int l, int r)
{
	vector<Record> Stack;
	for (int i = 0; i < Vec[x].size(); i ++)
	{
		int a = Find(Vec[x][i].first), b = Find(Vec[x][i].second);
		if (a == b)
			continue;
		if (Height[a] > Height[b])
			swap(a, b);
		Stack.push_back(Record(a, b, Height[b]));
		Fa[a] = b, Height[b] = max(Height[b], Height[a] + 1);
	}
	if (l == r - 1)
		ans += (Find(1) == Find(n)) ? T[r] - T[l] : 0;
	else
	{
		int mid = l + r >> 1;
		DFS(ls(x), l, mid);
		DFS(rs(x), mid, r);
	}
	while (!Stack.empty())
	{
		Fa[Stack.back().u] = Stack.back().u;
		Height[Stack.back().v] = Stack.back().h_v;
		Stack.pop_back();
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++)
		Fa[i] = i, Height[i] = 1;
	for (int i = 1, a, b, l, r; i <= m; i ++)
	{
		scanf("%d%d%d%d", &a, &b, &l, &r);
		E[i] = Edge(a, b, l, r + 1);
		T[i] = l, T[i + m] = r + 1;
	}
	sort(T + 1, T + 2 * m + 1);
	sz = unique(T + 1, T + 2 * m + 1) - T - 1;
	for (int i = 1; i <= m; i ++)
	{
		E[i].l = lower_bound(T + 1, T + sz + 1, E[i].l) - T;
		E[i].r = lower_bound(T + 1, T + sz + 1, E[i].r) - T;
		Add(1, 1, sz, E[i].l, E[i].r, E[i].a, E[i].b);
	}
	DFS(1, 1, sz);
	printf("%d\n", ans);
	return 0;
}
