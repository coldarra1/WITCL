#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn = (int)1e5 + 1;

namespace Memory {
	const int maxm = maxn * 18 + 1, maxl = maxm * 8 + 1;
	int pool[maxm], *pool_tail;
	LL info[maxl], *info_tail;

	inline void reset() {
		pool_tail = pool;
		info_tail = info;
	}
	inline int *ask32(int len) {
		int *ret = pool_tail;
		pool_tail += len;
		return ret;
	}
	inline LL *ask64(int len) {
		LL *ret = info_tail;
		info_tail += len;
		return ret;
	}
}

int n, qtot;
LL dp[maxn];
pair<int, int> seq[maxn], que[maxn];

inline void upd_min(LL &x, LL y) {
	x > y && (x = y);
}

inline bool cmp_y(int const &u, int const &v) {
	return que[u].second < que[v].second;
}

struct Segment {
	int ytot, *yque;
	LL *info;
} seg[maxn << 1 | 1];

inline int seg_idx(int L, int R) {
	return (L + R) | (L < R);
}

void seg_init_inner(Segment &rt, int L, int R) {
	if(L == R)
		return;
	int M = (L + R) >> 1;
	seg_init_inner(rt, L, M);
	seg_init_inner(rt, M + 1, R);
	LL *cur = rt.info + (seg_idx(L, R) << 2);
	LL *lft = rt.info + (seg_idx(L, M) << 2);
	LL *rht = rt.info + (seg_idx(M + 1, R) << 2);
	cur[0] = min(lft[0], rht[0]);
	cur[1] = min(lft[1], rht[1]);
	cur[2] = min(lft[2], rht[2]);
	cur[3] = min(lft[3], rht[3]);
}

void seg_init_outer(int L, int R) {
	static int ord[maxn];
	if(L < R) {
		int M = (L + R) >> 1;
		seg_init_outer(L, M);
		seg_init_outer(M + 1, R);
		inplace_merge(ord + L, ord + M + 1, ord + R + 1, cmp_y);
	} else {
		ord[L] = L;
	}
	Segment &rt = seg[seg_idx(L, R)];
	rt.ytot = 1;
	for(int i = L + 1; i <= R; ++i)
		rt.ytot += cmp_y(ord[i - 1], ord[i]);
	rt.yque = Memory::ask32(rt.ytot);
	rt.info = Memory::ask64(((rt.ytot - 1) << 1 | 1) << 2);
	for(int i = L, j = 0; i <= R; ++j) {
		int u = ord[i++], y = que[u].second, xL = que[u].first, xR = xL;
		for(int v; i <= R && !cmp_y(u, v = ord[i]); ++i) {
			int tmp = que[v].first;
			if(tmp < xL) {
				xL = tmp;
			} else if(tmp > xR) {
				xR = tmp;
			}
		}
		rt.yque[j] = y;
		LL *val = rt.info + (seg_idx(j, j) << 2);
		val[0] = -xR - y;
		val[1] = -xR + y;
		val[2] = xL - y;
		val[3] = xL + y;
	}
	seg_init_inner(rt, 0, rt.ytot - 1);
}

inline void seg_update_inner(Segment &rt, int y, LL val[]) {
	for(int L = 0, R = rt.ytot - 1; L <= R; ) {
		LL *cur = rt.info + (seg_idx(L, R) << 2);
		upd_min(cur[0], val[0]);
		upd_min(cur[1], val[1]);
		upd_min(cur[2], val[2]);
		upd_min(cur[3], val[3]);
		if(L == R)
			break;
		int M = (L + R) >> 1;
		if(y <= rt.yque[M]) {
			R = M;
		} else {
			L = M + 1;
		}
	}
}

inline void seg_update_outer(int pos) {
	int x = que[pos].first, y = que[pos].second;
	LL v = dp[pos], val[5] = {
		v - x - y,
		v - x + y,
		v + x - y,
		v + x + y
	};
	for(int L = 0, R = qtot - 1; L <= R; ) {
		seg_update_inner(seg[seg_idx(L, R)], y, val);
		if(L == R)
			break;
		int M = (L + R) >> 1;
		if(pos <= M) {
			R = M;
		} else {
			L = M + 1;
		}
	}
}

inline LL seg_query_left_inner(Segment &rt, int x, int y) {
	LL ret = LLONG_MAX;
	for(int L = 0, R = rt.ytot - 1; L <= R; ) {
		LL *cur = rt.info + (seg_idx(L, R) << 2);
		if(y <= rt.yque[L]) {
			upd_min(ret, cur[1] - y);
			break;
		} else if(y >= rt.yque[R]) {
			upd_min(ret, cur[0] + y);
			break;
		}
		int M = (L + R) >> 1;
		if(y <= rt.yque[M]) {
			LL *rht = rt.info + (seg_idx(M + 1, R) << 2);
			upd_min(ret, rht[1] - y);
			R = M;
		} else {
			LL *lft = rt.info + (seg_idx(L, M) << 2);
			upd_min(ret, lft[0] + y);
			L = M + 1;
		}
	}
	if(ret != LLONG_MAX)
		ret += x;
	return ret;
}

inline LL seg_query_right_inner(Segment &rt, int x, int y) {
	LL ret = LLONG_MAX;
	for(int L = 0, R = rt.ytot - 1; L <= R; ) {
		LL *cur = rt.info + (seg_idx(L, R) << 2);
		if(y <= rt.yque[L]) {
			upd_min(ret, cur[3] - y);
			break;
		} else if(y >= rt.yque[R]) {
			upd_min(ret, cur[2] + y);
			break;
		}
		int M = (L + R) >> 1;
		if(y <= rt.yque[M]) {
			LL *rht = rt.info + (seg_idx(M + 1, R) << 2);
			upd_min(ret, rht[3] - y);
			R = M;
		} else {
			LL *lft = rt.info + (seg_idx(L, M) << 2);
			upd_min(ret, lft[2] + y);
			L = M + 1;
		}
	}
	if(ret != LLONG_MAX)
		ret -= x;
	return ret;
}

inline LL seg_query_outer(int pos) {
	int x = que[pos].first, y = que[pos].second;
	LL ret = dp[pos];
	for(int L = 0, R = qtot - 1; L < R; ) {
		int M = (L + R) >> 1;
		if(pos <= M) {
			upd_min(ret, seg_query_right_inner(seg[seg_idx(M + 1, R)], x, y));
			R = M;
		} else {
			upd_min(ret, seg_query_left_inner(seg[seg_idx(L, M)], x, y));
			L = M + 1;
		}
	}
	return ret;
}

void solve() {
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", &seq[i].first, &seq[i].second);
		que[i] = seq[i];
		dp[i] = 0;
	}
	sort(que, que + n);
	qtot = unique(que, que + n) - que;

	Memory::reset();
	seg_init_outer(0, qtot - 1);

	LL ans = 0, sum = 0;
	int las = lower_bound(que, que + qtot, seq[0]) - que;
	for(int i = 1; i < n; ++i) {
		LL adt = abs(seq[i].first - seq[i - 1].first) + abs(seq[i].second - seq[i - 1].second);
		int pos = lower_bound(que, que + qtot, seq[i]) - que;
		LL best = seg_query_outer(pos) - adt;
		if(dp[las] > best) {
			upd_min(ans, dp[las] = best);
			seg_update_outer(las);
		}
		sum += adt;
		las = pos;
	}
	printf("%lld\n", ans + sum);
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