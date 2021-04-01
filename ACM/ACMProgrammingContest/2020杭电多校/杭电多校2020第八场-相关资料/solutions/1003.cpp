#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = (a); i <= int(b); i++)
#define per(i, a, b) for (int i = (a); i >= int(b); i--)
using namespace std;

const int maxn = 2e5, mod = 1e9 + 7;
int T, n, m, k, bs[40], a[maxn + 5], b[maxn + 5], nxt[maxn + 5];
char res[maxn + 5];

void insert(int x) {
	per(i, 30 - 1, 0) if (x >> i & 1) {
		if (!bs[i]) { bs[i] = x; break; }
		x ^= bs[i];
	}
}

int get(int x) {
	per(i, 30 - 1, 0) if (x >> i & 1) x ^= bs[i];
	return x;
}

int main() {
	scanf("%d", &T);
	while (T --> 0) {
		scanf("%d %d %d", &n, &m, &k);
		rep(i, 1, n) scanf("%d", &a[i]);
		rep(i, 1, m) scanf("%d", &b[i]);
		memset(bs, 0, sizeof(bs));
		for (int i = 1, x; i <= k; i++) {
			scanf("%d", &x);
			insert(x);
		}
		rep(i, 1, n) a[i] = get(a[i]);
		rep(i, 1, m) b[i] = get(b[i]);
		for (int i = 2, t = 0; i <= m; i++) {
			while (t && b[t + 1] != b[i]) t = nxt[t];
			if (b[t + 1] == b[i]) t++;
			nxt[i] = t;
		}
		for (int i = 1, t = 0; i <= n; i++) {
			while (t && b[t + 1] != a[i]) t = nxt[t];
			if (b[t + 1] == a[i]) t++;
			if (t == m) res[i - m + 1] = '1', t = nxt[t];
			else if (i >= m) res[i - m + 1] = '0';
		}
		res[n - m + 2] = 0;
		int ans = 0;
		per(i, n - m + 1, 1) {
			ans = (2ll * ans + (res[i] == '1')) % mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}