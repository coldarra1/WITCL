#include <bits/stdc++.h>
using namespace std;

const int P = 1e9 + 7;

pair<vector<long long>, int> brute_force(int n, int *E, int *G) {
	vector<int> a(E, E + n + 1);
	vector<int> b(G, G + n + 1);
	vector<int> id(n + 1);
	iota(id.begin(), id.end(), 0);
	sort(id.begin() + 1, id.end(), [&](int u, int v) {
		int su = a[u] <= b[u];
		int sv = a[v] <= b[v];
		if (su != sv) return su > sv;
		if (su > 0) return a[u] < a[v];
		return b[u] > b[v];
	});
	vector<vector<long long>> dp(2, vector<long long>(n + 1, 1LL << 60));
	dp[0][0] = 0;
	for (int i = n; i > 0; i--) {
		fill(dp[n - i + 1 & 1].begin(), dp[n - i + 1 & 1].end(), 1LL << 60);
		for (int j = 0; j <= n - i; j++) {
			dp[n - i + 1 & 1][j + 1] = min(dp[n - i + 1 & 1][j + 1], max(0LL, dp[n - i & 1][j] - b[id[i]]) + a[id[i]]);
			dp[n - i + 1 & 1][j] = min(dp[n - i + 1 & 1][j], dp[n - i & 1][j]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = (ans + dp[n & 1][i] % P * i) % P;
	}
	return make_pair(dp[n & 1], ans);
}

int E[330000], G[330000];

int main() {
	freopen("../Testdata/input.txt", "r", stdin);
	freopen("../Testdata/answer.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int ncase;
	for (cin >> ncase; ncase--; ) {
		int n; cin >> n;
		for (int i = 1; i <= n; i++) cin >> E[i];
		for (int i = 1; i <= n; i++) cin >> G[i];
		cout << brute_force(n, E, G).second << "\n";
	}
	return 0;
}
