#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("result.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << "const long long g[] = {0";
	for (int i = 1; i <= 4000; i++) {
		vector<int> d(2500000, 1);
		long long L = (i - 1) * 2500000LL + 1, R = i * 2500000LL;
		for (int j = 2; j * 1LL * j <= R; j++) {
			for (int k = max<long long>(j, (L + j - 1) / j) * j - L; k < 2500000; k += j) {
				d[k] = j;
			}
		}
		long long sum = 0;
		for (int x : d) {
			sum += x;
		}
		cout << ", " << sum;
	}
	cout << "};\n";
	return 0;
}
