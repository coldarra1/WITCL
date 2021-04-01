#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define N 200000 + 5

int n, m, rt, cnt, Deg[N], Leaf[N];
vector<int> Vec[N];

void dfs(int z, int fa)
{
	if (Deg[z] == 1)
		Leaf[++ cnt] = z;
	for (int d : Vec[z])
		if (d != fa)
			dfs(d, z);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i ++)
	{
		scanf("%d%d", &u, &v);
		Vec[u].push_back(v);
		Vec[v].push_back(u);
		Deg[u] ++, Deg[v] ++;
	}
	for (int i = 1; !rt && i <= n; i ++)
		if (Deg[i] > 1)
			rt = i;
	dfs(rt, 0);
	m = (cnt + 1) / 2;
	printf("%d\n", m);
	for (int i = 1; i * 2 <= cnt; i ++)
		printf("%d %d\n", Leaf[i + m], Leaf[i]);
	if (cnt & 1)
		printf("%d %d\n", rt, Leaf[m]);
	return 0;
}
