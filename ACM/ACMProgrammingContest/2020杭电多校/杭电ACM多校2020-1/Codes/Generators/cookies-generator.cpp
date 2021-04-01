#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
inline T rnd(T l, T r) {
	assert(l <= r);
	return uniform_int_distribution<T>(l, r)(rng);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("input.txt", "w", stdout);
	auto print = [&](const vector<long long> &p, long long n, int m, long long k) {
		cout << n << ' ' << m << ' ' << k << '\n';
		for (int i = 0; i < m; i++) {
			cout << p[i] << " \n"[i == m - 1];
		}
	};
	for (int runs = 0; runs < 20; runs++) {
		int m = rnd(1, 100000);
		vector<long long> p(m);
		for (int i = 0; i < m; i++) {
			p[i] = rnd(1LL, 10000000000LL);
		}
		long long n = rnd(1LL, 10000000000LL);
		long long r = n;
		for (int i = 0; i < m; i++) {
			if (runs % 10 == 9) {
				assert(r % p[i] != 0);
			}
			r -= r / p[i];
		}
		long long k = max<long long>(1, rnd(0LL, r));
		if (rnd(0, 5) == 0 && r < n) {
			k = rnd(r + 1, n);
		}
		if (runs % 10 == 8) k = 1;
		if (runs % 10 == 9) k = r;
		print(p, n, m, k);
	}
	for (int runs = 0; runs < 10; runs++) {
		int m = rnd(1, 100000);
		vector<long long> p(m);
		for (int i = 0; i < m; i++) {
			p[i] = rnd(1LL, 10000000000LL);
		}
		long long n = rnd(1LL, 10000000000LL);
		long long r = n;
		for (int i = 0; i < m; i++) {
			r -= r / p[i];
		}
		long long k = rnd(1LL, min<long long>(1e7, r));
		print(p, n, m, k);
	}
	for (int runs = 0; runs < 20; runs++) {
		int m = rnd(1, 100);
		vector<long long> p(m);
		for (int i = 0; i < m; i++) {
			p[i] = rnd(10, 500);
		}
		long long n = rnd(1LL, 10000000000LL);
		long long r = n;
		for (int i = 0; i < m; i++) {
			r -= r / p[i];
		}
		long long k = max<long long>(1, rnd(0LL, r));
		if (rnd(0, 1) && r < n) {
			k = rnd(r + 1, n);
		}
		print(p, n, m, k);
	}
	{
		int m = 100000;
		vector<long long> p(m);
		for (int i = 0; i < m; i++) {
			p[i] = rnd(100000LL, 10000000000LL);
		}
		long long n = 10000000000LL;
		long long r = n;
		for (int i = 0; i < m; i++) {
			r -= r / p[i];
		}
		long long k = max<long long>(1, rnd(0LL, r));
		print(p, n, m, k);
	}
	print({10000000000LL}, 10000000000LL, 1, 10000000000LL - 1);
	print({3}, 10000000000LL, 1, 10000000000LL - 10000000000LL / 3);
	return 0;
}
