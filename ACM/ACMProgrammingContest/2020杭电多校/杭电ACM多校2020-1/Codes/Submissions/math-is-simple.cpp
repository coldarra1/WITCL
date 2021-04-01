#include <bits/stdc++.h>
using namespace std;

const int N = 1e8 + 1;
const int M = 1e4 + 1;
const int P = 998244353;

int r[N], p[M];
vector<int> primes;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	for (int i = 1; i < N; i++) r[i] = i == 1 ? 1 : r[P % i] * 1LL * (P - P / i) % P;
	for (int i = 1; i < N; i++) r[i] = (r[i] + r[i - 1]) % P;
	for (int i = 2; i < M; i++) if (!p[i]) {
		primes.push_back(i);
		for (int j = i * i; j < M; j += i) p[j] = i;
	}
	int ncase;
	for (assert(cin >> ncase && ncase > 0 && ncase <= 1e4); ncase--; ) {
		int n; assert(cin >> n && n > 1 && n <= 1e8);
		int m = n;
		vector<int> q;
		for (int x : primes) {
			if (x * x > m) break;
			if (m % x == 0) {
				while (m % x == 0) m /= x;
				q.push_back(x);
			}
		}
		if (m > 1) q.push_back(m);
		vector<int> d(1 << q.size());
		int ans = 0;
		for (int s = 0; s < 1 << q.size(); s++) {
			d[s] = s == 0 ? 1 : d[s - (s & -s)] * q[__builtin_ctz(s)];
			ans = (ans + (P + (1 - (__builtin_popcount(s) & 1) * 2) * r[n / d[s]]) * 1LL * (r[d[s]] + P - r[d[s] - 1])) % P;
		}
		if (n == 2) ans = 0;
		ans = (ans * 1LL * (P + r[n] - r[n - 1]) + (P + 1) / 2) % P;
		cout << ans << '\n';
	}
	return 0;
}
