#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int F[MAXN*2];
void init() {
	memset(F, -1, sizeof(F));
}
int a[MAXN], b[MAXN];
int c[MAXN*2];
int find(int x) {
	if (F[x] == -1) return x;
	return F[x] = find(F[x]);
}
bool vis[MAXN*2];
void bing(int x, int y) {
	int t1 = find(x);
	int t2 = find(y);
	if (t1 == t2) {
		vis[t1] = true;
		return;
	}
	F[t1] = t2;
	if (vis[t1]) vis[t2] = true;
}

int main() {
	int T;
	scanf("%d", &T);
	int iCase = 0;
	while (T--) {
		iCase++;
		init();
		memset(vis, false, sizeof(vis));
		int n;
		scanf("%d", &n);
		int tot = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &a[i], &b[i]);
			c[tot++] = a[i];
			c[tot++] = b[i];
		}
		sort(c, c+tot);
		tot = unique(c, c+tot) - c;
		for (int i = 0; i < n; i++) {
			int x = lower_bound(c, c+tot, a[i]) - c;
			int y = lower_bound(c, c+tot, b[i]) - c;
			bing(x, y);
		}
		int ans = tot;
		for (int i = 0; i < tot; i++)
			if (F[i] == -1 && !vis[i])
				ans--;
		printf("Case #%d: %d\n", iCase, ans);
	}
	return 0;
}
