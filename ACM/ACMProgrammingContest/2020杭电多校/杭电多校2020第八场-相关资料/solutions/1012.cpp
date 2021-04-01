#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= int(b); i++)
#define per(i, a, b) for (int i = (a); i >= int(b); i--)
#define fi first
#define se second
using namespace std;

typedef pair<int, int> P;
const int maxn = 5e3, maxm = maxn * 2;
int T, n, f[maxn + 5], l[maxn + 5], r[maxn + 5];
vector<int> G[maxn + 5];
vector<P> vec[maxn + 5];

struct event {
	int x, y;
	event(int x = 0, int y = 0): x(x), y(y) {}
	bool operator < (const event &o) const {
		return x == o.x ? y < o.y : x < o.x;
	}
} ev[maxm + 5];

void dfs(int u, int par = 0) {
	f[u] = 0;
	for (int i = 0, v; i < G[u].size(); i++) {
		v = G[u][i];
		if (v == par) continue;
		dfs(v, u);
		f[u] += f[v] + 1;
	}
	int m = 0;
	for (int i = 0, v; i < G[u].size(); i++) {
		v = G[u][i];
		if (v == par) continue;
		rep(j, 0, vec[v].size() - 1) {
			P x = vec[v][j];
			ev[++m] = event(x.fi, 1);
			ev[++m] = event(x.se + 1, -1);
		}
	}
	ev[++m] = event(l[u], 999999999);
	ev[++m] = event(r[u] + 1, -999999999);
	sort(ev + 1, ev + m + 1);
	int cur = -999999999, mx = -999999999;
	vector<P> res;
	rep(i, 1, m - 1) {
		cur += ev[i].y;
		if (cur > mx) mx = cur, vector<P>().swap(res);
		if (cur == mx && ev[i].x != ev[i + 1].x) res.push_back(P(ev[i].x, ev[i + 1].x));
	}
	f[u] -= mx;
	vector<P>().swap(vec[u]);
	for (int l = 0, r = 0; l < res.size(); l = r + 1, r = l) {
		while (r < res.size() - 1 && res[r + 1].fi == res[r].se) r++;
		vec[u].push_back(P(res[l].fi, res[r].se - 1));
	}
	// puts("=====");
	// printf("%d %d %d\n", u, f[u], m);
	// rep(i, 0, vec[u].size() - 1) {
	// 	printf("[%d, %d]\n", vec[u][i].fi, vec[u][i].se);
	// }
}

int main() {
	scanf("%d", &T);
	while (T --> 0) {
		scanf("%d", &n);
		rep(i, 1, n) vector<int>().swap(G[i]);
		for (int i = 1, u, v; i < n; i++) {
			scanf("%d %d", &u, &v);
			G[u].push_back(v), G[v].push_back(u);
		}
		rep(i, 1, n) scanf("%d %d", &l[i], &r[i]);
		dfs(1);
		int res = f[1], dt = 1;
		rep(i, 0, vec[1].size() - 1) {
			P x = vec[1][i];
			if (x.fi <= 0 && x.se >= 0) dt = 0;
		}
		printf("%d\n", res + dt);
	}
	return 0;
}