#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int, int> Pii;
#define N 200000 + 5
#define INF 0x7f7f7f7f

int q, root, tot;
set<Pii> Set;
set<Pii> ::iterator it;

struct Node
{
	int l, r, sz, fa, val, mnval;
	Pii prio, mxprio;
	
	Node(){}
	Node(const Pii &p) : prio(p), mxprio(p)
	{
		l = r = fa = val = mnval = 0;
		sz = 1;
	}
}h[N];

inline void update(int x)
{
	h[x].sz = h[h[x].l].sz + h[h[x].r].sz + 1;
	h[x].mnval = min(h[x].val, min(h[h[x].l].mnval, h[h[x].r].mnval));
	h[x].mxprio = h[x].r ? h[h[x].r].mxprio : h[x].prio;
}

void Init()
{
	h[0].val = h[0].mnval = INF;
	h[1] = make_pair(-1, 0);
	h[2] = make_pair(INF, 0);
	tot = root = 2;
	h[2].l = 1, h[1].fa = 2;
	h[1].val = INF;
	h[2].val = h[2].prio.first - h[1].prio.first;
	update(2);
}

void zig(int x)
{
	int y = h[x].fa, z = h[y].fa;
	if (y == h[z].l) h[z].l = x;
	if (y == h[z].r) h[z].r = x;
	h[x].fa = z, h[y].fa = x;
	h[y].l = h[x].r, h[h[x].r].fa = y, h[x].r = y;
	update(y), update(x);
}

void zag(int x)
{
	int y = h[x].fa, z = h[y].fa;
	if (y == h[z].l) h[z].l = x;
	if (y == h[z].r) h[z].r = x;
	h[x].fa = z, h[y].fa = x;
	h[y].r = h[x].l, h[h[x].l].fa = y, h[x].l = y;
	update(y), update(x);
}

void Splay(int x, int fa)
{
	while (h[x].fa != fa)
	{
		int y = h[x].fa, z = h[y].fa;
		if (x == h[y].l && y == h[z].l)
			zig(y), zig(x);
		else if (x == h[y].l)
			zig(x);
		else if (x == h[y].r && y == h[z].r)
			zag(y), zag(x);
		else zag(x);
	}
	if (!fa) root = x;
}

void Insert(const Pii &prio)
{
	h[++ tot] = Node(prio);
	if (!root)
	{
		root = tot;
		return ;
	}
	int z, p = root;
	while (p)
	{
		z = p;
		if (prio < h[z].prio)
			p = h[z].l;
		else p = h[z].r;
	}
	Splay(z, 0);
	if (prio < h[z].prio)
	{
		int pre = h[z].l;
		for (; h[pre].r; pre = h[pre].r) ;
		Splay(pre, z);
		h[tot].fa = pre, h[pre].r = tot;
		h[z].val = h[z].prio.first - h[tot].prio.first;
		h[tot].val = h[tot].prio.first - h[pre].prio.first;
		update(tot), update(pre), update(z);
	}
	else
	{
		int nxt = h[z].r;
		for (; h[nxt].l; nxt = h[nxt].l) ;
		Splay(nxt, z);
		h[tot].fa = nxt, h[nxt].l = tot;
		h[nxt].val = h[nxt].prio.first - h[tot].prio.first;
		h[tot].val = h[tot].prio.first - h[z].prio.first;
		update(tot), update(nxt), update(z);
	}
	Splay(tot, 0);
}

void Erase(int t)
{
	Splay(t, 0);
	int pre = h[t].l, nxt = h[t].r;
	for (; h[pre].r; pre = h[pre].r) ;
	for (; h[nxt].l; nxt = h[nxt].l) ;
	Splay(pre, t);
	Splay(nxt, t);
	h[nxt].val = h[nxt].prio.first - h[pre].prio.first;
	h[nxt].fa = 0, h[nxt].l = pre, h[pre].fa = nxt;
	update(nxt);
	root = nxt;
}

int LowerBound(int x, const Pii &prio)
{
	if (h[x].prio < prio)
		return LowerBound(h[x].r, prio);
	if (h[h[x].l].mxprio < prio)
		return x;
	return LowerBound(h[x].l, prio);
}

int main()
{
	Init();
	scanf("%d", &q);
	for (int op, x, i = 1; i <= q; i ++)
	{
		scanf("%d%d", &op, &x);
		if (op == 1)
		{
			Pii p = make_pair(x, i);
			Set.insert(p);
			Insert(p);
		}
		else if (op == 2)
		{
			Pii p = make_pair(x, 0);
			Set.erase(Set.lower_bound(p));
			Erase(LowerBound(root, p));
		}
		else
		{
			bool ok = false;
			Pii p = make_pair(x, 0);
			it = Set.lower_bound(p);
			if (it != Set.begin())
			{
				int a = (*(-- it)).first;
				if (it != Set.begin())
				{
					int b = (*(-- it)).first;
					if (a + b > x)
						ok = true;
				}
			}
			int t = LowerBound(root, p);
			Splay(t, 0);
			int mn = h[t].val;
			if (h[t].r)
				mn = min(mn, h[h[t].r].mnval);
			if (mn < x)
				ok = true;
			puts(ok ? "Yes" : "No");
		}
	}
	return 0;
}
