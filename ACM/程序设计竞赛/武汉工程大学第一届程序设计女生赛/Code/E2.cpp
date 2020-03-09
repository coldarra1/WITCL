# include <iostream>

using namespace std;

const int N = 1e6 + 5, mod = 1e9 + 7;
int F[N], G[N];

int quickpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1)
			res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}

void init() {
	F[0] = G[0] = 1;
	for (int i = 1; i < N; i++) {
		F[i] = 1ll * F[i - 1] * i % mod;
		G[i] = 1ll * G[i - 1] * quickpow(i, mod - 2) % mod;
	}
	return;
}

int main() {
	init();
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		int k = n / 2;
		cout << 1ll * F[n] * G[k] % mod * G[n - k] % mod * quickpow(quickpow(2, mod - 2), n) % mod << endl;
	}
	return 0;
}
