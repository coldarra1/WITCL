#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5;

namespace flow {

	struct edge {
		int to, cap, flow, rev;
	};
	vector<edge> g[maxn + 10];
	int s, t, ndcnt, d[maxn + 10], cur[maxn + 10];
	queue<int> q;

	void init(int ss, int tt, int nn) {
		s = ss; t = tt;
		for (int i = 1; i <= ndcnt; ++i) g[i].clear();
		ndcnt = nn;
	}

	void addedge(int l, int r, int w) {
		g[l].push_back((edge){r, w, 0, (int)g[r].size()});
		g[r].push_back((edge){l, 0, 0, (int)g[l].size() - 1});
	}

	bool bfs() {
		for (int i = 1; i <= ndcnt; ++i)
			d[i] = i == s ? 0 : -1;
		q.push(s);
		while (!q.empty()) {
			int p = q.front(); q.pop();
			for (int i = 0; i < (int)g[p].size(); ++i) {
				edge e = g[p][i];
				if (e.cap > e.flow && d[e.to] == -1) {
					d[e.to] = d[p] + 1; q.push(e.to);
				}
			}
		}
		return d[t] != -1;
	}

	int dfs(int p, int a) {
		if (p == t) return a;
		int ans = 0, now;
		for (int &i = cur[p]; i < (int)g[p].size(); ++i) {
			edge &e = g[p][i];
			if (e.cap > e.flow && d[p] + 1 == d[e.to]) {
				now = dfs(e.to, min(a, e.cap - e.flow));
				e.flow += now; g[e.to][e.rev].flow -= now;
				ans += now; a -= now; if (!a) break;
			}
		}
		return ans;
	}

	int solve() {
		int ans = 0;
		while (bfs()) {
			for (int i = 1; i <= ndcnt; ++i) cur[i] = 0;
			ans += dfs(s, 1e9);
		}
		return ans;
	}

}

int n, x[maxn + 10], y[maxn + 10];
int l[maxn + 10], r[maxn + 10], sl, sr;

int main() {
	int T, lim = 5e5; scanf("%d", &T);
	assert(T == 100);
	while (T--) {
		int n; scanf("%d", &n);
		assert(n >= 1 && n <= 100000);
		lim -= n;
		for (int i = 1; i <= n; ++i) {
			int a, b; scanf("%d%d", &a, &b);
			assert(a >= 1 && a <= 1000000000);
			assert(b >= 1 && b <= 1000000000);
			x[i] = a + b; y[i] = a - b;
		}
		sl = sr = 0;
		for (int i = 1; i <= n; ++i) {
			l[++sl] = x[i]; r[++sr] = y[i];
		}
		sort(l + 1, l + sl + 1);
		sl = unique(l + 1, l + sl + 1) - l - 1;
		sort(r + 1, r + sr + 1);
		sr = unique(r + 1, r + sr + 1) - r - 1;
		flow::init(1, 2, 2 + sl + sr);
		for (int i = 1; i <= sl; ++i)
			flow::addedge(1, i + 2, 1);
		for (int i = 1; i <= sr; ++i)
			flow::addedge(i + sl + 2, 2, 1);
		for (int i = 1; i <= n; ++i) {
			x[i] = lower_bound(l + 1, l + sl + 1, x[i]) - l;
			y[i] = lower_bound(r + 1, r + sr + 1, y[i]) - r;
			flow::addedge(x[i] + 2, y[i] + sl + 2, 1);
		}
		printf("%d\n", flow::solve());
	}
	assert(!lim);
}
