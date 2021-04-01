#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	freopen("input.txt", "w", stdout);
	cout << 100000 << endl;
	for (int i = 1; i <= 50000; i++) {
		cout << i << "\n";
		cout << 1000000000 - i + 1 << "\n";
	}
	return 0;
}
