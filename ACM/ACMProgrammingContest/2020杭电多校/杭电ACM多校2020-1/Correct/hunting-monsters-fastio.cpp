#include <bits/stdc++.h>
using namespace std;

const int P = 1e9 + 7;

inline char get_char() {
	static char a[1 << 16];
	static int n = 0, p = 0;
	if (p == n) n = fread(a, 1, 1 << 16, stdin), p = 0;
	return n ? a[p++] : 0;
}

inline void read(int &x) {
	char c;
	while ((c = get_char()) <= ' ' && c);
	int sgn = 1;
	for (x = 0; c > ' '; c = get_char()) c == '-' ? sgn = -1 : x = x * 10 + sgn * (c - '0');
}

int main() {
	int ncase;
	for (read(ncase); ncase--; ) {
		int n; read(n);
		vector<pair<int, int>> p(n + 1), A, B;
		for (int i = 1; i <= n; i++) read(p[i].first);
		for (int i = 1; i <= n; i++) read(p[i].second);
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
	return 0;
}
