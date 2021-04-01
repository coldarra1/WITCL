#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 4548 + 5
#define M 5000 + 5
#define S 40 + 5
#define LOGN 14
#define Mod 998244353
#define LIM 7985954824000000000LL

int n, m, q, tot, root, Head[N], Cur[N], Log[N], Upper[N], Dep[N], Go[N][LOGN];

struct Edge
{
	int next, node;
	string str;
}E[N << 1];

struct ACAM
{
	int fail, flag, son[26];
}h[S];

struct Matrix
{
	int r, c, num[S][S];
	static Matrix IdelMatrix(int columns)
	{
		Matrix res;
		res.r = 1, res.c = columns;
		for (int i = 0; i < columns; i ++)
			res.num[0][i] = (i == 0);
		return res;
	}
	static Matrix Transfer(const string &str)
	{
		Matrix res;
		res.r = res.c = tot + 1;
		for (int i = 0; i < res.r; i ++)
			for (int j = 0; j < res.c; j ++)
				res.num[i][j] = 0;
		for (int u = 0; u <= tot; u ++)
			for (char c : str)
				res.num[u][h[u].son[c - 'a']] ++;
		return res;
	}
	Matrix operator * (const Matrix &obj) const
	{
		Matrix res;
		res.r = r, res.c = obj.c;
		for (int i = 0; i < res.r; i ++)
			for (int j = 0, k; j < res.c; j ++)
			{
				LL tmp = 0;
				for (int k = 0; k < c; k ++)
                {
					tmp += 1LL * num[i][k] * obj.num[k][j];
                    if (tmp >= LIM) tmp -= LIM;
                }
				res.num[i][j] = tmp % Mod;
			}
		return res;
	}
};

vector<Matrix> Up[N], Down[N];

inline void addedge(int u, int v, string&& str)
{
	static int cnt = 0;
	E[++ cnt].next = Head[u], Head[u] = cnt;
	E[cnt].node = v, E[cnt].str = str;
}

inline int Inc(int u, int v)
{
	return u + v - (u + v >= Mod ? Mod : 0);
}

void BuildFail()
{
	vector <int> Q;
	for (int i = 0; i < 26; i ++)
		if (h[0].son[i])
			Q.push_back(h[0].son[i]);
	for (int i = 0; i < Q.size(); i ++)
	{
		int u = Q[i], fail_u = h[u].fail;
		for (int j = 0; j < 26; j ++)
		{
			if (!h[u].son[j])
				h[u].son[j] = h[fail_u].son[j];
			else
			{
				int d = h[u].son[j];
				h[d].fail = h[fail_u].son[j];
				h[d].flag |= h[h[d].fail].flag;
				Q.push_back(d);
			}
		}
	}
	for (int u = 0; u <= tot; u ++)
		if (h[u].flag)
			for (int j = 0; j < 26; j ++)
				h[u].son[j] = u;
}

void dfs(int rt, bool construct)
{
	for (int i = 1; i <= n; i ++)
		Cur[i] = Head[i], Go[i][0] = 0;
	vector<int> Sta;
	Sta.push_back(rt);
	while (!Sta.empty())
	{
		int z = Sta.back();
		if (Cur[z] && E[Cur[z]].node == Go[z][0])
			Cur[z] = E[Cur[z]].next; 
		if (Cur[z])
		{
			int d = E[Cur[z]].node;
			Dep[d] = Dep[z] + 1, Go[d][0] = z;
			if (construct)
			{
				Up[d].resize(Upper[Dep[d]] + 1);
				Down[d].resize(Upper[Dep[d]] + 1);
				Up[d][0] = Down[d][0] = Matrix::Transfer(E[Cur[z]].str);
				for (int j = 1, x = z; Go[x][j - 1]; x = Go[x][j - 1], j ++)
				{
					Go[d][j] = Go[x][j - 1];
					if (j <= Upper[Dep[d]])
					{
						Up[d][j] = Up[d][j - 1] * Up[x][j - 1];
						Down[d][j] = Down[x][j - 1] * Down[d][j - 1];
					}
				}
			}
			Sta.push_back(d);
			Cur[z] = E[Cur[z]].next;
		}
		else Sta.pop_back();
	}
}

void Handle()
{
	static int Cnt[N];
	for (int i = 0; i < n; i ++)
		Cnt[i] = 0;
	dfs(1, false);
	int delta = 0, mx = 0;
	for (int i = 1; i <= n; i ++)
		Cnt[Dep[i]] ++, mx = max(mx, Dep[i]);
	for (int w = 0; (1 << w) <= mx && w <= 9; w ++)
	{
		int cnt0 = 0, cnt1 = 0;
		for (int i = 0; i <= mx; i ++)
		{
			if ((i & (1 << w) - 1) != delta)
				continue ;
			if ((i + delta >> w) & 1)
				cnt1 += Cnt[i];
			else cnt0 += Cnt[i];
		}
		if (cnt0 > cnt1)
			delta += (1 << w);
	}
	if (delta)
	{
		root = n + delta;
		for (int i = delta; i > 1; i --)
			addedge(n + i, n + i - 1, "");
		addedge(n + 1, 1, "");
	}
	else root = 1;
	n += delta;
	for (int i = 2; i <= n; i ++)
	{
		Log[i] = Log[i >> 1] + 1;
		Upper[i] = (i & 1) ? 0 : Upper[i >> 1] + 1;
	}
}

int LCA(int u, int v)
{
	if (Dep[u] < Dep[v])
		swap(u, v);
	for (int t = Dep[u] - Dep[v]; t; t -= (t & -t))
		u = Go[u][Log[t & -t]];
	if (u == v) return u;
	for (int i = Log[n]; Go[u][0] != Go[v][0]; i --)
		if (Go[u][i] != Go[v][i])
			u = Go[u][i], v = Go[v][i];
	return Go[u][0];
}

vector<pair<int, int>> GetPath(int src, int dst)
{
	vector<pair<int, int>> res;
	for (int x = src, j; x != dst; x = Go[x][j])
	{
		for (j = Upper[Dep[x]]; Dep[x] - (1 << j) < Dep[dst]; j --) ;
		res.emplace_back(x, j);
	}
	return res;
}

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1, u, v; i < n; i ++)
	{
		static char s[S];
		static bool Flag[26];
		scanf("%d%d%s", &u, &v, s);
		for (int j = 0; j < 26; j ++)
			Flag[j] = false;
		addedge(u, v, s);
		addedge(v, u, s);
	}
	Handle();
	int tot_len = 0;
	for (int i = 1; i <= m; i ++)
	{
		static char s[S];
		scanf("%s", s);
		int u = 0;
		for (int j = 0; s[j]; j ++)
		{
			tot_len ++;
			int d = s[j] - 'a';
			if (!h[u].son[d])
			h[u].son[d] = ++ tot;
			u = h[u].son[d];
		}
		h[u].flag = true;
	}
	BuildFail();
	dfs(root, true);
	for (int i = 1, u, v; i <= q; i ++)
	{
		scanf("%d%d", &u, &v);
		int lca = LCA(u, v);
		Matrix f = Matrix::IdelMatrix(tot + 1);
		vector<pair<int, int>> u_path = GetPath(u, lca);
		vector<pair<int, int>> v_path = GetPath(v, lca);
		for (const pair<int, int> &p : u_path)
			f = f * Up[p.first][p.second];
		reverse(v_path.begin(), v_path.end());
		for (const pair<int, int> &p : v_path)
			f = f * Down[p.first][p.second];
		int res = 0;
		for (int x = 0; x <= tot; x ++)
			if (h[x].flag)
				res = Inc(res, f.num[0][x]);
		printf("%d\n", res);
	}
	return 0;
}
