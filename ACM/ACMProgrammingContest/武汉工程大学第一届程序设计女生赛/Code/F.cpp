# include <iostream>

using namespace std;

int exgcd(int a, int b, int& x, int& y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int quickpow(int a, int b, int mod) {
	int res = 1;
	while (b) {
		if (b & 1)
			res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}

int violence(int a, int b, int mod) {
	int res = 1;
	while (b--)
		res = 1ll * res * a % mod;
	return res;
}

int main() {
	int p, q, m, e = 65537;
	cin >> p >> q >> m;
	int n = p * q, phi = (p - 1) * (q - 1);
	int x, y;
	exgcd(e, phi, x, y);
	cout << (x % phi + phi) % phi << endl << violence(m, e, n) << endl;
	return 0;
}
