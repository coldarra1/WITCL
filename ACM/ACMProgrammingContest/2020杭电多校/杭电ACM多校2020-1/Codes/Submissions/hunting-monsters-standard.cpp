#include <bits/stdc++.h>
using namespace std;

const int P = 1e9 + 7;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int ncase, nsum = 0;
	for (assert(cin >> ncase); ncase--; ) {
		int n; assert(cin >> n);
		nsum += n;
		assert(n > 0 && n <= 300000);
		vector<pair<int, int>> p(n + 1), A, B;
		for (int i = 1; i <= n; i++) assert(cin >> p[i].first);
		for (int i = 1; i <= n; i++) assert(cin >> p[i].second);
		for (int i = 1; i <= n; i++) assert(min(p[i].first, p[i].second) > 0 && max(p[i].first, p[i].second) <= 1e9);
		for (int i = 1; i <= n; i++) p[i].first <= p[i].second ? A.push_back(p[i]) : B.emplace_back(p[i].second, p[i].first);
		sort(A.begin(), A.end());
		sort(B.begin(), B.end());
		priority_queue<int, vector<int>, greater<int>> Q;
		long long ans = 0;
		vector<long long> a(1), b(1);
		for (auto t : B) {
			while (!Q.empty()) {
				int cur = Q.top() + ans;
				if (cur > t.first) break;
				ans = cur;
				b.push_back(ans);
				Q.pop();
			}
			if (!Q.empty()) {
				int cur = Q.top() + ans - t.first;
				Q.pop();
				Q.push(cur);
			}
			ans = t.first;
			Q.push(t.second - t.first);
		}
		while (!Q.empty()) b.push_back(ans += Q.top()), Q.pop();
		long long minc = 0, cur = 0;
		for (auto t : A) {
			cur -= t.first;
			minc = min(minc, cur);
			a.push_back(-minc);
			cur += t.second;
		}
		int pos = 0, neg = 0, ret = 0;
		long long last = 0, gain = 0;
		while (pos < A.size() || neg < B.size()) {
			while (pos < A.size() && a[pos+1] == last) gain += A[pos].second - A[pos].first, pos++, ret = (ret + last % P * (pos + neg)) % P;
			long long nlast = pos < A.size() ? a[pos+1] : (1LL << 60);
			while (neg < B.size() && b[neg+1] < gain + nlast) neg++, ret = (ret + max(last, b[neg] - gain) % P * (pos + neg)) % P;
			last = nlast;
		}
		cout << ret << "\n";
	}
	assert(nsum <= 2500000);
	return 0;
}
