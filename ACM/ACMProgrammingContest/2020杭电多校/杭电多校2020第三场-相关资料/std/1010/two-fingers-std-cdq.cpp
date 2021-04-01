#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> Point;
typedef pair<int, LL> Info;

const int maxn = (int)1e5 + 1, maxm = maxn << 1 | 1;
const LL INF = (LL)1e18;

int n, tot, ord[maxn];
Point seq[maxn], que[maxn];

int ytot, LOG, yord[maxn], yque[maxn];
int st, tim[maxn];
LL bit[maxn];

int m, pL[maxn], pR[maxn];
Info f[maxm];

inline void upd_min(LL &x, LL y) {
	x > y && (x = y);
}

inline bool cmp(int const &u, int const &v) {
	return ord[u] < ord[v];
}

LL solve(int L, int R) {
	if(L == R) {
		LL ret = 0;
		if(L > 0) {
			int idx = pL[L];
			LL dis = abs(seq[L].first - seq[L - 1].first) + abs(seq[L].second - seq[L - 1].second);
			ret = f[idx].second - dis;
			f[idx] = make_pair(ord[L - 1], ret);
		}
		return ret;
	}
	int M = (L + R) >> 1;
	LL ret = solve(L, M);

	int cnt = 0;
	static int pos[maxn];
	for(int i = M + 1; i <= R; ++i)
		pos[cnt++] = i;

	LL cost1 = 1LL * (pR[L] - pL[L]) * cnt, cost2 = 4LL * (pR[L] - pL[L] + cnt) * LOG;
	if(cost1 <= cost2) {
		for(int i = 0; i < cnt; ++i) {
			int u = pos[i], qx = seq[u].first, qy = seq[u].second;
			LL &res = f[pL[u]].second;
			for(int j = pL[L]; j < pR[L]; ++j) {
				int v = f[j].first, px = que[v].first, py = que[v].second;
				upd_min(res, f[j].second + abs(px - qx) + abs(py - qy));
			}
		}
	} else {
		sort(pos, pos + cnt, cmp);

		++st;
		for(int i = 0, j = pL[L]; i < cnt; ++i) {
			int u = pos[i], qx = seq[u].first, qy = seq[u].second;
			for(int v, px; j < pR[L] && (px = que[v = f[j].first].first) <= qx; ++j) {
				int py = que[v].second;
				LL tmp = f[j].second - px - py;
				for(int y = yord[v] + 1; y <= ytot; y += y & -y)
					if(tim[y] == st) {
						upd_min(bit[y], tmp);
					} else {
						tim[y] = st;
						bit[y] = tmp;
					}
			}
			LL tmp = INF;
			for(int y = yord[ord[u]] + 1; y > 0; y -= y & -y)
				if(tim[y] == st)
					upd_min(tmp, bit[y]);
			if(tmp < INF)
				upd_min(f[pL[u]].second, tmp + qx + qy);
		}

		++st;
		for(int i = 0, j = pL[L]; i < cnt; ++i) {
			int u = pos[i], qx = seq[u].first, qy = seq[u].second;
			for(int v, px; j < pR[L] && (px = que[v = f[j].first].first) <= qx; ++j) {
				int py = que[v].second;
				LL tmp = f[j].second - px + py;
				for(int y = yord[v] + 1; y > 0; y -= y & -y)
					if(tim[y] == st) {
						upd_min(bit[y], tmp);
					} else {
						tim[y] = st;
						bit[y] = tmp;
					}
			}
			LL tmp = INF;
			for(int y = yord[ord[u]] + 1; y <= ytot; y += y & -y)
				if(tim[y] == st)
					upd_min(tmp, bit[y]);
			if(tmp < INF)
				upd_min(f[pL[u]].second, tmp + qx - qy);
		}

		++st;
		for(int i = cnt - 1, j = pR[L] - 1; i >= 0; --i) {
			int u = pos[i], qx = seq[u].first, qy = seq[u].second;
			for(int v, px; j >= pL[L] && (px = que[v = f[j].first].first) >= qx; --j) {
				int py = que[v].second;
				LL tmp = f[j].second + px - py;
				for(int y = yord[v] + 1; y <= ytot; y += y & -y)
					if(tim[y] == st) {
						upd_min(bit[y], tmp);
					} else {
						tim[y] = st;
						bit[y] = tmp;
					}
			}
			LL tmp = INF;
			for(int y = yord[ord[u]] + 1; y > 0; y -= y & -y)
				if(tim[y] == st)
					upd_min(tmp, bit[y]);
			if(tmp < INF)
				upd_min(f[pL[u]].second, tmp - qx + qy);
		}

		++st;
		for(int i = cnt - 1, j = pR[L] - 1; i >= 0; --i) {
			int u = pos[i], qx = seq[u].first, qy = seq[u].second;
			for(int v, px; j >= pL[L] && (px = que[v = f[j].first].first) >= qx; --j) {
				int py = que[v].second;
				LL tmp = f[j].second + px + py;
				for(int y = yord[v] + 1; y > 0; y -= y & -y)
					if(tim[y] == st) {
						upd_min(bit[y], tmp);
					} else {
						tim[y] = st;
						bit[y] = tmp;
					}
			}
			LL tmp = INF;
			for(int y = yord[ord[u]] + 1; y <= ytot; y += y & -y)
				if(tim[y] == st)
					upd_min(tmp, bit[y]);
			if(tmp < INF)
				upd_min(f[pL[u]].second, tmp - qx - qy);
		}
	}

	upd_min(ret, solve(M + 1, R));

	cnt = 0;
	static Info g[maxm];
	for(int i = pL[L], j = pL[M + 1]; i < pR[L] || j < pR[M + 1]; )
		if(j >= pR[M + 1] || (i < pR[L] && f[i].first < f[j].first)) {
			g[cnt++] = f[i++];
		} else {
			g[cnt++] = f[j++];
			if(i < pR[L] && g[cnt - 1].first == f[i].first)
				upd_min(g[cnt - 1].second, f[i++].second);
		}
	memcpy(f + pL[L], g, cnt * sizeof(Info));
	pR[L] = pL[L] + cnt;

	return ret;
}

void solve() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d%d", &seq[i].first, &seq[i].second);
	memcpy(que, seq, n * sizeof(Point));
	sort(que, que + n);
	tot = unique(que, que + n) - que;
	for(int i = 0; i < n; ++i)
		ord[i] = lower_bound(que, que + tot, seq[i]) - que;

	for(int i = 0; i < tot; ++i)
		yque[i] = que[i].second;
	sort(yque, yque + tot);
	ytot = unique(yque, yque + tot) - yque;
	for(int i = 0; i < tot; ++i)
		yord[i] = lower_bound(yque, yque + ytot, que[i].second) - yque;
	for(LOG = 1; (1 << LOG) <= ytot; ++LOG);

	pL[0] = m = 0;
	for(int i = 0; i < tot; ++i)
		f[m++] = make_pair(i, 0LL);
	pR[0] = m;
	LL adt = 0;
	for(int i = 1; i < n; ++i) {
		pL[i] = m;
		LL dis = abs(seq[i].first - seq[i - 1].first) + abs(seq[i].second - seq[i - 1].second);
		f[m++] = make_pair(ord[i], dis);
		adt += dis;
		pR[i] = m;
	}

	st = 0;
	memset(tim + 1, 0, ytot * sizeof(int));
	LL ans = solve(0, n - 1);
	printf("%lld\n", ans + adt);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int Case = 1; Case <= T; ++Case) {
		// printf("Case #%d:\n", Case);
		solve();
	}
	return 0;
}