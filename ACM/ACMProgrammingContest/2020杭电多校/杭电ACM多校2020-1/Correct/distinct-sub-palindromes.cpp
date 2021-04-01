#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int ncase;
	for (cin >> ncase; ncase--; ) {
		int n; cin >> n;
		cout << (vector<int>){1, 26, 676, 17576, 15600}[min(n, 4)] << "\n";
	}
	return 0;
}
