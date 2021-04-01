#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
inline T next_int(T l, T r) {
	return uniform_int_distribution<T>(l, r)(rng);
}

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 53, 59, 61, 67};

int main() {
	freopen("input.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	vector<int> a;
	for (int i = 2; i <= 100; i++) a.push_back(i);
	for (int i = 0; i < 2000; i++) a.push_back(1e8 - i);
	for (int i = 0; i < 7000; i++) a.push_back(next_int(101, 99998000));
	int n = 9699690;
	for (int i = 1; i <= 10; i++) a.push_back(n * i);
	while (a.size() < 9777) {
		int x = 1;
		while (1) {
			int y = primes[next_int(0, (int)primes.size() - 1)];
			if (x % y == 0) continue;
			if (x * 1LL * y > 1e8) {
				break;
			}
			x *= y;
		}
		a.push_back(x);
	}
	shuffle(a.begin(), a.end(), rng);
	cout << a.size() << "\n";
	for (int x : a) {
		cout << x << "\n";
	}
	return 0;
}
