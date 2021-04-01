#include <bits/stdc++.h>
using namespace std;


const int MAXN = 100010;
struct Edge {
	int to, next;
} edge[MAXN*2];
int head[MAXN], tot;
void init() {
	tot = 0;
	memset(head, -1, sizeof(head));
}
void addedge(int u, int v) {
	edge[tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot++;
}
int V[MAXN];
int dep[MAXN];
void getDep(int u, int fa) {
	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].to;
		if (v == fa) continue;
		dep[v] = dep[u] + 1;
		getDep(v, u);
	}
}
struct Node {
	int l, r;
	int Max;
	int lazy;
	int Max2;
} segTree[MAXN<<2];
void push_up(int i) {
	if (segTree[i].l == segTree[i].r)
		return;
	segTree[i].Max = max(segTree[i<<1].Max, segTree[(i<<1)|1].Max);
}
void push_down(int i) {
	if (segTree[i].l == segTree[i].r)
		return;
	if (segTree[i].lazy != 0) {
		segTree[i<<1].Max += segTree[i].lazy;
		segTree[i<<1].lazy += segTree[i].lazy;
		segTree[(i<<1)|1].Max += segTree[i].lazy;
		segTree[(i<<1)|1].lazy += segTree[i].lazy;
		segTree[i].lazy = 0;
	}
}
int id[MAXN];
void build(int i, int l, int r) {
	segTree[i].l = l;
	segTree[i].r = r;
	segTree[i].lazy = 0;
	segTree[i].Max = 0;
	segTree[i].Max2 = -1;
	if (l == r) {
		id[l] = i;
	 	return;
	}
	int mid = (l+r)>>1;
	build(i<<1, l, mid);
	build((i<<1)|1, mid+1, r);
}
void update(int i, int l, int r, int c) {
	if (segTree[i].l == l && segTree[i].r == r) {
		segTree[i].Max += c;
		segTree[i].lazy += c;
		return;
	}
	push_down(i);
	int mid = (segTree[i].l + segTree[i].r) >> 1;
	if (r <= mid) update(i<<1, l, r, c);
	else if (l > mid) update((i<<1)|1, l, r, c);
	else {
		update(i<<1, l, mid, c);
		update((i<<1)|1, mid+1, r, c);
	}
	push_up(i);
}

void update2(int u, int c) {
	int i = id[u];
	segTree[i].Max2 = c;
	i /= 2;
	while (i) {
		segTree[i].Max2 = max(segTree[i<<1].Max2, segTree[(i<<1)|1].Max2);
		i /= 2;
	}
}
int query2(int i, int x) {
	if (segTree[i].Max2 < x) return 0;
	if (segTree[i].l == segTree[i].r) return segTree[i].l;
	if (segTree[(i<<1)|1].Max2 >= x)
		return query2((i<<1)|1, x);
	else return query2(i<<1, x);
}

int query(int i, int W) {
	if (segTree[i].Max < W) return -1;
	if (segTree[i].l == segTree[i].r)
		return segTree[i].l;
	push_down(i);
	if (segTree[(i<<1)|1].Max >= W)
		return query((i<<1)|1, W);
	else 
		return query(i<<1, W);
}
int A[MAXN];

int W;
void dfs(int u, int pre) {
	int t = query2(1, V[u]) + 1;
	update(1, t, dep[u], 1);
	update2(dep[u], V[u]);

	int ret = query(1, W);
	if (ret == -1) A[u] = MAXN;
	else A[u] = dep[u] - ret + 1;

	for (int i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].to;
		if (v == pre) continue;
		dfs(v, u);
	}

	update(1, t, dep[u], -1);
	update2(dep[u], -1);
}

int B[MAXN];

int main() {
	int n;
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d%d", &n, &W);
		for (int i = 1; i <= n; i++)
			scanf("%d", &V[i]);
		init();
		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			addedge(u, v);
			addedge(v, u);
		}
		dep[1] = 1;
		getDep(1, 1);
		int maxH = 0;
		for (int i = 1; i <= n; i++)
			maxH = max(maxH, dep[i]);
		build(1, 1, maxH);
		dfs(1, 1);

		sort(A+1, A+n+1);
		memset(B, 0, sizeof(B));
		for (int i = 1; i <= n; i++) {
			if (A[i] <= n) B[A[i]]++;
		}
		for (int i = 2; i <= n; i++) B[i] += B[i-1];
		for (int i = 1; i <= n; i++)
			printf("%d%c", B[i], i == n ? '\n' : ' ');
	}
	return 0;
}
