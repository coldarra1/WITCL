# include <iostream>
# include <cstdio>
# include <cstring>
# include <algorithm>

using namespace std;

typedef pair<int, int> PII;
const int N = 1e6 + 5;
int n, m, pos;
int val[N], E[N];
PII w[N], nums[N];

struct segment_tree {
	int l, r;
	int add, max_val, idx;
} T[N << 2];

void update(int p) {
	int lp = p << 1, rp = lp | 1;
	if (T[lp].max_val == T[rp].max_val) {
		T[p].max_val = T[lp].max_val;
		T[p].idx = min(T[lp].idx, T[rp].idx);
	} else if (T[lp].max_val > T[rp].max_val) {
		T[p].max_val = T[lp].max_val;
		T[p].idx = T[lp].idx;
	} else {
		T[p].max_val = T[rp].max_val;
		T[p].idx = T[rp].idx;
	}
	return;
}

void push_down(int p) {
	if (!T[p].add || T[p].l == T[p].r)
		return;
	int lp = p << 1, rp = lp | 1;
	T[lp].max_val += T[p].add;
	T[rp].max_val += T[p].add;
	T[lp].add += T[p].add;
	T[rp].add += T[p].add;
	T[p].add = 0;
	return;
}

void build(int p, int l, int r) {
	T[p].l = l, T[p].r = r;
	if (l == r) {
		T[p].max_val = 0;
		T[p].idx = nums[l].second;
		return;
	}
	int mid = l + r >> 1, lp = p << 1, rp = lp | 1;
	build(lp, l, mid);
	build(rp, mid + 1, r);
	update(p);
	return;
}

void change(int p, int l, int r, int c) {
	if (l <= T[p].l && r >= T[p].r) {
		T[p].max_val += c;
		T[p].add += c;
		return;
	}
	push_down(p);
	int mid = T[p].l + T[p].r >> 1, lp = p << 1, rp = lp | 1;
	if (l <= mid)
		change(lp, l, r, c);
	if (r > mid)
		change(rp, l, r, c);
	update(p);
	return;
}

int get_idx(int val) {
	int l = 0, r = pos;
	while (l < r) {
		int mid = l + r + 1 >> 1;
		if (nums[mid].first <= val)
			l = mid;
		else
			r = mid - 1;
	}
	return l;
}

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", val + i);
	for (int i = 1; i <= n; i++)
		scanf("%d", E + i);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &w[i].first);
		w[i].second = i;
	}
	sort(w + 1, w + m + 1);
	nums[0].first = -2e9;
	for (int i = 1; i <= m; ) {
		nums[++pos] = w[i];
		int j = i;
		while (j <= m && w[i].first == w[j].first)
			j++;
		i = j;
	}
	build(1, 1, pos);
	for (int i = 1; i <= n; i++) {
		int p = get_idx(val[i]);
		if (!p)
			continue;
		change(1, 1, p, E[i]);
	}
	printf("%d\n", T[1].idx);
	return 0;
}

