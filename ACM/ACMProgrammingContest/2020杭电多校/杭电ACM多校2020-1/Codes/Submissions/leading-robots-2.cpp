#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	int ncase;
	for (cin >> ncase; ncase--; ) {
		int n; cin >> n;
		set<pair<int, int>> S;
		vector<pair<int, int>> a(n), b(n);
		for (auto &t : a) {
			cin >> t.first >> t.second;
		}
		sort(a.begin(), a.end());
		for (int i = 0; i < n - 1; i++) {
			if (a[i] == a[i + 1]) {
				S.insert(a[i]);
			}
		}
		a.resize(n = unique(a.begin(), a.end()) - a.begin());
		reverse(a.begin(), a.end());
		int m = 1;
		for (int i = 1; i < n; i++) {
			if (a[i].second > a[m - 1].second) {
				a[m++] = a[i];
			}
		}
		n = m;
		b[0].first = 0, b[0].second = 1;
		vector<int> q = {0};
		for (int i = 1; i < n; i++) {
			while (!q.empty()) {
				int id = q.back();
				b[i] = {a[id].first - a[i].first, a[i].second - a[id].second};
				if (1LL * b[i].first * b[id].second > 1LL * b[i].second * b[id].first) break;
				q.pop_back();
			}
			q.push_back(i);
		}
		int ans = 0;
		for (int x : q) {
			if (!S.count(a[x])) ans++;
		}
		cout << ans << '\n';
	}
	return 0;
}
