#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 9;
const int C = 276601605; // 1 / sqrt(5)
const int A = 691504013; // (1 + sqrt(5)) / 2
const int AA = 691504012; // A ^ -1
const int B = 308495997; // (1 - sqrt(5)) / 2

inline int modExp(int a, long long n) {
	int ret = 1;
	for (; n; n >>= 1, a = (long long)a * a % mod) if (n & 1) ret = (long long)ret * a % mod;
	return ret;
}

inline void add(int &u, int v) {
	u += v;
	if (u >= mod) u -= mod;
}

const int N = 110000;

int f[N], g[N], r[N];

void init() {
	f[0] = g[0] = f[1] = g[1] = r[1] = 1;
	for (int i = 2; i < N; i++) {
		f[i] = (long long)f[i - 1] * i % mod;
		r[i] = (long long)(mod -  mod / i) * r[mod % i] % mod;
		g[i] = (long long)g[i - 1] * r[i] % mod;
	}
}

inline int nCm(int n, int m) {
	if (m < 0 || m > n) return 0;
	return (long long)f[n] * g[m] % mod * g[n - m] % mod;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	init();
	int tcase; cin >> tcase;
	while (tcase--) {
		long long n, c; int k; cin >> n >> c >> k;
		int DD = (long long)modExp(AA, c) * modExp(B, c) % mod;
		int q = modExp(modExp(A, c), k);
		int ans = 0;
		int n1 = (n + 1) % mod;
		int n2 = (n + 1) % (mod - 1);
		for (int i = 0; i <= k; i++) {
			int cur = nCm(k, i);
			if (i & 1) cur = mod - cur;
			if (q == 1) add(ans, (long long)cur * n1 % mod);
			else add(ans, (long long)cur * (modExp(q, n2) + mod - 1) % mod * modExp(q-1, mod-2) % mod);
			q = (long long)q * DD % mod;
		}
		cout << (long long)ans * modExp(C, k) % mod << "\n";
	}
	return 0;
}
