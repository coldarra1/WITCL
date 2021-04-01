#include <bits/stdc++.h>
using namespace std;

const long long inf = 1LL << 60;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int ncase;
	for (cin >> ncase; ncase--; ) {
		int n; cin >> n;
		vector<int> B(n + 1), ID(n + 1), next(n + 1), q(n + 1);
		vector<long long> A(n + 1), s(n + 1), dp(n + 2);
		vector<vector<long long>> b(18, vector<long long>(n + 1));
		vector<pair<long long, int>> a(n + 1);
		for (int i = 1; i <= n; i++) cin >> A[i];
		for (int i = 1; i <= n; i++) cin >> B[i];
		for (int i = 1; i <= n; i++) ID[i] = i;
		sort(ID.begin() + 1, ID.end(), [&](int u, int v) { return A[u] < A[v]; });
		for (int i = 1; i <= n; i++) a[i] = {A[ID[i]], B[ID[i]]};
		for (int i = 1; i <= n; i++) A[i] = a[i].first, B[i] = a[i].second;
		long long high = 0, curt = 0;
		for (int i = 1; i <= n; i++) {
			high = max(high, curt - A[i]);
			curt = max(curt, A[i]) + B[i];
			s[i] = s[i - 1] + B[i];
		}
		for (int i = n; i > 0; i--) {
			next[i] = i + 1;
			for (int &j = next[i]; j <= n && A[i] + B[i] > A[j] + B[j]; j = next[j]);
		}
		for (int i = 1; i <= n; i++) b[0][i] = A[i] - s[i - 1];
		for (int i = 1; 1 << i <= n; i++) {
			for (int j = 1; j <= n; j++) b[i][j] = max(b[i - 1][j], (j + (1 << i - 1) <= n ? b[i - 1][j + (1 << i - 1)] : -inf));
		}
		auto bmax = [&](int l, int r) {
			int k = 31 - __builtin_clz(r - l + 1);
			return max(b[k][l], b[k][r - (1 << k) + 1]);
		};
		auto check = [&](long long t) {
			dp[n + 1] = inf;
			int qn = 0;
			for (int i = n, j = n; i > 0; i--) {
				while (j > i && A[j] >= A[i] + t) j--;
				dp[i] = -inf; q[qn++] = i + 1;
				for (int k = qn - 1, l = min(j + 1, next[i]); k >= 0 && q[k] <= l; k--) {
					int u = q[k];
					long long now = min(dp[u], A[i] + B[i] + t);
					if (dp[u] <= now) qn--;
					if (now - s[u - 1] > dp[i] - s[i - 1]) {
						long long cur = (u == i + 1 ? A[i] + B[i] - s[i] : bmax(i + 1, u - 1) + B[i]);
						if (now - s[u - 1] >= cur) dp[i] = now - s[u - 1] + s[i - 1];
					}
				}
				if (dp[i] < A[i]) return false;
			}
			return true;
		};
		long long lo = -1, hi = high;
		while (hi - lo > 1) {
			long long mid = lo + hi >> 1;
			(check(mid) ? hi : lo) = mid;
		}
		cout << hi << "\n";
	}
	return 0;
}
