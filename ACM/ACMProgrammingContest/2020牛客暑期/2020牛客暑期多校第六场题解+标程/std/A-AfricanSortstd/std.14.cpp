#include <bits/stdc++.h>

using namespace std;

const int maxn = 100010;
const int mod = 998244353;

int qpow(int x, int y) {
	int ret = 1;
	while (y) {
		if (y & 1) ret = 1LL * ret * x % mod;
		x = 1LL * x * x % mod;
		y >>= 1;
	}
	return ret;
}

int n, m, f[maxn], sum = 0, vis[maxn], p[maxn];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 2; i <= n; i++) {
		f[i] = 1LL * (sum + i) % mod * qpow(i-1, mod-2) % mod * i % mod;
		sum = (sum + 1LL * f[i] * qpow(i, mod-2) % mod) % mod;
	}
	while (m--) {
		for (int i = 1; i <= n; i++) {
			vis[i] = 0;
			scanf("%d", &p[i]);
		}
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			if (!vis[i]) {
				int c = i, l = 0;
				do {
					vis[c] = 1;
					++ l;
					c = p[c];
				} while (c != i);
				ans = (ans + f[l]) % mod;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}
