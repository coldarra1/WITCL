#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 1000 + 5
#define D 1000000 + 5
#define E 10000000 + 5
#define INF 1000000000000LL

int n, m, S, T, tot, Head[D], Id[N][N];
LL W[N][N][2], Dis[D];
bool Flag[D];

struct Edge
{
	int next, node;
	LL w;
}h[E];

struct Node
{
	int id;
	LL dis;
	Node(){}
	Node(int id, LL dis) : id(id), dis(dis) {}
	bool operator < (const Node &rhs) const
	{
		return dis > rhs.dis;
	}
};

priority_queue<Node> Q;

inline void addedge(int u, int v, LL w)
{
	h[++ tot].next = Head[u], Head[u] = tot;
	h[tot].node = v, h[tot].w = w;
}

void Read()
{
	scanf("%d%d", &n, &m);
	S = 0, T = n * (n - 1) / 2 + 1;
	for (int l = 1, id = 0; l < n; l ++)
		for (int r = l + 1; r <= n; r ++)
		{
			W[l][r][0] = W[l][r][1] = INF;
			Id[l][r] = ++ id;
		}
	for (int i = 1, l, r; i <= m; i ++)
	{
		char dir;
		LL w;
		scanf("%d %d %c %lld", &l, &r, &dir, &w);
		int d = dir == 'L' ? 0 : 1;
		W[l][r][d] = min(W[l][r][d], w);
	}
}

void Build()
{
	for (int l = 1, id = 1; l < n; l ++)
		for (int r = l + 1; r <= n; r ++, id ++)
		{
			if (r < n)
			{
				LL w = W[l][r][0];
				addedge(Id[l][r], Id[l][r + 1], w);
				addedge(Id[l][r + 1], Id[l][r], w);
			}
			if (l > 1)
			{
				LL w = W[l][r][1];
				addedge(Id[l][r], Id[l - 1][r], w);
				addedge(Id[l - 1][r], Id[l][r], w);
			}
		}
	for (int l = 1, r = n; l < n; l ++)
	{
		LL w = W[l][r][0];
		addedge(S, Id[l][r], w);
	}
	for (int l = 1, r = 2; r <= n; r ++)
	{
		LL w = W[l][r][1];
		addedge(Id[l][r], T, w);
	}
}

void Dijkstra()
{
	memset(Dis, 0x3f, sizeof(Dis));
	Dis[S] = 0;
	Q.push(Node(S, 0));
	while (!Q.empty())
	{
		Node x;
		do
		{
			x = Q.top();
			Q.pop();
		} while (!Q.empty() && (Flag[x.id] || Dis[x.id] != x.dis));
		if (Flag[x.id] || Dis[x.id] != x.dis)
			continue ;
		Flag[x.id] = true;
		for (int i = Head[x.id]; i; i = h[i].next)
		{
			int d = h[i].node;
			LL w = h[i].w;
			if (!Flag[d] && Dis[x.id] + w < Dis[d])
				Q.push(Node(d, Dis[d] = Dis[x.id] + w));
		}
	}
}

int main()
{
	Read();
	Build();
	Dijkstra();
	if (Dis[T] >= INF)
		puts("-1");
	else printf("%lld\n", Dis[T]);
	return 0;
}
