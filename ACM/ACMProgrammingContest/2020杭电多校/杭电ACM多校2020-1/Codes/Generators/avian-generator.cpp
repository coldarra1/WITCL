#include <bits/stdc++.h>

using namespace std;

int random() {
	return (rand() << 15) | rand();
}

int random(int n) {
	return random() % n;
}

int random(const int &l, const int &r) {
	return l + random(r - l);
}

long long randomll() {
	return ((long long)random() << 30) | random();
}

long long randomll(const long long &n) {
	return randomll() % n;
}

long long randomll(const long long &l, const long long &r) {
	return l + randomll(r - l);
}

long double randoml() {
	return (long double)randomll() / (1ll << 60);
}

long double randoml(const long double &n) {
	return randoml() * n;
}

long double randoml(const long double &l, const long double &r) {
	return l + randoml(r - l);
}

void get(int &x, int &y, int &z) {
	for (; ; ) {
		x = random(2) == 0 ? 0 : random(-180, 180 + 1);
		y = random(2) == 0 ? 0 : random(-120, 120 + 1);
		z = random(2) == 0 ? 0 : random(-60, 60 + 1);
		int w = x * x + y * y + z * z;
		if (w == 0 || 100 <= w)
			return;
	}
}

int main() {
	ios::sync_with_stdio(false);
	
	srand(time(NULL));

	freopen("data.in", "w", stdout);

	cout << 1 << endl;
	cout << 60 << " " << 0 << " " << 0 << " " << 340 << " " << 3 << endl;
	cout << 2 << endl;
	cout << 90 << " " << 0 << " " << 0 << " " << 500 << " " << 1 << endl;
	cout << 0 << " " << -30 << " " << 0 << " " << 200 << " " << 3 << endl;
	cout << 1 << endl;
	cout << 0 << " " << 0 << " " << 30 << " " << 100 << " " << 6 << endl;

	int nmax = 0;
	for (int T = 4; T <= 10000; T++) {
		int n = random(5, 11);
		nmax = max(nmax, n);
		cout << n << endl;
		for (int i = 0; i < n; i++) {
			int x, y, z;
			get(x, y, z);
			cout <<
			x << " " <<
			y << " " <<
			z << " " <<
			random(100, 500 + 1) << " " <<
			random(5, 10 + 1) << endl;
		}
	}
	
	cerr << "maxn = " << nmax << endl;

	return 0;
}
