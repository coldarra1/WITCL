#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int ncase;
	for (cin >> ncase; ncase--; ) {
		string s; cin >> s; s.push_back(0);
		int n = s.length(), cur = 0, mid = 1, start = 0;
		vector<int> d(n + 1);
		d[1] = 1;
		for (int i = 1; i < n; i++) {
			if (s[i] == s[cur]) {
				d[i + 1] = i - cur + d[cur + 1];
				if (++cur == mid) cur = start;
			} else if (s[i] > s[cur]) {
				mid = i + 1;
				cur = start;
				d[i + 1] = cur + 1;
			} else {
				int temp = mid - start;
				start += (i - start) / temp * temp;
				i = cur = start;
				mid = start + 1;
				d[i + 1] = i + 1;
			}
		}
		int ans = 0;
		for (int i = n - 1; i > 0; i--) ans = (1112LL * ans + d[i]) % 1000000007;
		cout << ans << "\n";
	}
	return 0;
}
