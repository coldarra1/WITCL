#include <bits/stdc++.h>
using namespace std;

long long rnd() {
	return (1LL * rand() << 45) | (1LL * rand() << 30) | rand() << 15 | rand();
}

int main() {
	freopen("input.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << 200 << "\n";
	for (int N = 1; N <= 5; N++) for (int C = 1; C <= 5; C++) for (int K = 1; K <= 5; K++) cout << N << " " << C << " " << K << "\n";
	for (int tcase = 0; tcase < 70; tcase++) {
		cout << rnd() % 1000000000000000000LL + 1 << " " << rnd() % 1000000000000000000LL + 1 << " " << rnd() % 100000 + 1 << "\n";
	}
	cout << 1000000000000000000LL << " " << 1000000000000000000LL << " " << 100000 << endl;
	cout << 100000000000000000LL << " " << 1000000000000000000LL << " " << 100000 << endl;
	cout << 1000000000000000000LL << " " << 100000000000000000LL << " " << 100000 << endl;
	cout << 1000000000000000000LL << " " << 1000000000000000000LL << " " << 10000 << endl;
	cout << 999999999999999999LL << " " << 999999999999999999LL << " " << 9999 << endl;
	return 0;
}
