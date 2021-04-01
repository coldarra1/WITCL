#include <bits/stdc++.h>
using namespace std;

const long long inf = 1LL << 60;

long long correct_solution(int n, const vector<long long> &T, const vector<int> &D) {
	vector<pair<long long, int>> a(n + 1);
	vector<long long> s(n + 1, 0);
	for (int i = 1; i <= n; i++) a[i].first = T[i];
	for (int i = 1; i <= n; i++) a[i].second = D[i];
	sort(a.begin() + 1, a.end());
	for (int i = 1; i <= n; i++) s[i] = s[i - 1] + a[i].second;
	vector<int> next(n + 1);
	for (int i = n; i > 0; i--) {
		next[i] = i + 1;
		for (int &j = next[i]; j <= n && a[i].first + a[i].second > a[j].first + a[j].second; j = next[j]);
	}
	vector<vector<long long>> b(18, vector<long long>(n + 1));
	const long long inf = 1LL << 60;
	for (int i = 1; i <= n; i++) b[0][i] = a[i].first - s[i - 1];
	for (int i = 1; 1 << i <= n; i++) {
		for (int j = 1; j <= n; j++) b[i][j] = max(b[i - 1][j], (j + (1 << i - 1) <= n ? b[i - 1][j + (1 << i - 1)] : -inf));
	}
	auto bmax = [&](int l, int r) {
		if (l > r) return -inf;
		int k = 31 - __builtin_clz(r - l + 1);
		return max(b[k][l], b[k][r - (1 << k) + 1]);
	};
	vector<long long> dp(n + 2);
	vector<int> q(n + 1);
	auto check = [&](long long t) {
		dp[n + 1] = inf;
		int qn = 0;
		for (int i = n, j = n; i > 0; i--) {
			while (j > i && a[j].first >= a[i].first + t) j--;
			dp[i] = -inf;
			q[qn++] = i + 1;
			while (qn > 0) {
				int u = q[qn - 1];
				if (u > min(j + 1, next[i])) break;
				long long cur = (u == i + 1 ? a[i].first - s[i] : bmax(i + 1, u - 1));
				long long now = min(dp[u], a[i].first + a[i].second + t);
				if (now - s[u - 1] >= cur + a[i].second) dp[i] = max(dp[i], now - s[u - 1] + s[i - 1]);
				if (a[i].first + a[i].second + t >= dp[u]) qn--;
				else break;
			}
			if (dp[i] < a[i].first) return false;
		}
		return true;
	};
	long long lo = -1, hi = 1LL << 50;
	while (hi - lo > 1) {
		long long mid = lo + hi >> 1;
		(check(mid) ? hi : lo) = mid;
	}
	return hi;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int ncase;
	for (cin >> ncase; ncase--; ) {
		int n; cin >> n;
		vector<long long> A(n + 1);
		vector<int> B(n + 1);
		for (int i = 1; i <= n; i++) cin >> A[i];
		for (int i = 1; i <= n; i++) cin >> B[i];
		cout << correct_solution(n, A, B) << "\n";
	}
	return 0;
}
