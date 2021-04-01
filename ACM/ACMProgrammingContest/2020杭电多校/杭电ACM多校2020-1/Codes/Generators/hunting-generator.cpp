#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int next_int(int l, int r) {
	return uniform_int_distribution<int>(l, r)(rng);
}

const int N = 330000;
const int P = 1e9 + 7;
const long long inf = 1LL << 60;

int a[N], b[N], id[N];
pair<int, int> p[N];

void print(int n, ostream &cout = cout) {
	vector<int> id(n + 1);
	iota(id.begin(), id.end(), 0);
	shuffle(id.begin() + 1, id.end(), rng);
	cout << n << "\n";
	for (int i = 1; i <= n; i++) cout << a[id[i]] << " \n"[i == n];
	for (int i = 1; i <= n; i++) cout << b[id[i]] << " \n"[i == n];
}

pair<vector<long long>, int> solution(int n, int *E, int *G) {
	vector<long long> a(n + 1);
	vector<long long> b(n + 1);
	vector<pair<long long, long long>> p(n + 1);
	for (int i = 1; i <= n; i++) p[i].first = E[i];
	for (int i = 1; i <= n; i++) p[i].second = G[i];
	vector<pair<long long, long long>> A, B;
	for (int i = 1; i <= n; i++) {
		if (p[i].first <= p[i].second) A.push_back(p[i]);
		else B.push_back(p[i]);
	}
	sort(A.begin(), A.end());
	sort(B.begin(), B.end(), [&](pair<long long, long long> &lhs, pair<long long, long long> &rhs) {
		return lhs.second < rhs.second;
	});
	{
		multiset<long long> S;
		int sz = 0;
		long long last = 0;
		for (auto t : B) {
			long long now = t.second;
			while (!S.empty()) {
				auto it = S.begin();
				if (*it + last <= now) {
					last += *it;
					b[++sz] = last;
					S.erase(it);
				} else {
					break;
				}
			}
			if (!S.empty()) {
				auto it = S.begin();
				long long cur = *it + last - now;
				assert(cur > 0);
				S.insert(cur);
				S.erase(it);
			}
			last = now;
			S.insert(t.first - t.second);
		}
		while (!S.empty()) {
			auto it = S.begin();
			last += *it;
			b[++sz] = last;
			S.erase(it);
		}
	}
	{
		long long need = 0, last = 0;
		int sz = 0;
		for (auto t : A) {
			last -= t.first;
			if (last < -need) need = -last;
			last += t.second;
			a[++sz] = need;
		}
	}
	int pos = 0, neg = 0, ret = 0;
	long long last = 0, gain = 0;
	vector<long long> ans(1);
	while (pos < A.size() || neg < B.size()) {
		while (pos < A.size() && a[pos+1] == last) gain += A[pos].second - A[pos].first, pos++, ans.push_back(last), ret = (ret + last % P * (pos + neg)) % P;
		long long nlast = 1LL<<60;
		if (pos < A.size()) nlast = a[pos+1];
		while (neg < B.size() && b[neg+1] < gain + nlast) neg++, ans.push_back(max(last, b[neg] - gain)), ret = (ret + max(last, b[neg] - gain) % P * (pos + neg)) % P;
		last = nlast;
	}
	assert(pos + neg == n);
	return make_pair(ans, ret);
}

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
	vector<vector<long long> > dp(2, vector<long long>(n + 1, inf));
	dp[1][0] = 0;
	for (int i = n; i > 0; i--) {
		fill(dp[n - i & 1].begin(), dp[n - i & 1].end(), inf);
		for (int j = 0; j <= n - i; j++) {
			dp[n - i & 1][j + 1] = min(dp[n - i & 1][j + 1], max(0LL, dp[n - i & 1][j] - b[id[i]]) + a[id[i]]);
			dp[n - i & 1][j] = min(dp[n - i & 1][j], dp[n - i & 1][j]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		ans = (ans + dp[n & 1][i] % P * i) % P;
	}
	return make_pair(dp[n & 1], ans);
}

void generate(int N, int M) {
	int cnt = 0;
	int n = next_int(1, N);
	for (int i = 1; i <= n; i++) {
		a[i] = next_int(1, M);
		b[i] = next_int(1, M);
	}
	auto ans = solution(n, a, b);
	auto temp = brute_force(n, a, b);
	assert(ans == temp);
	print(n);
}

void generate_large(int tp) {
	int n = next_int(5000, 10000);
	if (tp < 2) {
		vector<int> c(2 * n);
		for (int i = 1; i <= 2 * n; i++) c[i - 1] = next_int(1, 1e9);
		sort(c.begin(), c.end());
		for (int i = 1; i <= n; i++) a[i] = c[i * 2 - 2], b[i] = c[i * 2 - 1];
		if (tp) for (int i = 1; i <= n; i++) swap(a[i], b[i]);
		int op = 50 * next_int(0, 10);
		while (op--) {
			int u = next_int(1, n);
			int v = next_int(1, n);
			swap(a[u], a[v]);
		}
	} else {
		int p = next_int(1, n - 1);
		int q = n - p;
		vector<int> c(2 * n);
		for (int i = 1; i <= 2 * n; i++) c[i - 1] = next_int(1, 1e9);
		sort(c.begin(), c.end());
		vector<int> id(2 * n);
		for (int i = 1; i <= 2 * n; i++) id[i - 1] = i - 1;
		random_shuffle(id.begin(), id.end());
		sort(id.begin(), id.begin() + 2 * p);
		sort(id.begin() + 2 * p, id.end());
		for (int i = 1; i <= n; i++) a[i] = c[id[2 * i - 2]], b[i] = c[id[2 * i - 1]];
		for (int i = p + 1; i <= n; i++) swap(a[i], b[i]);
		int op = 50 * next_int(0, 10);
		while (op--) {
			int cmd = next_int(0, 1);
			int u, v;
			if (cmd) {
				u = next_int(1, p), v = next_int(1, p);
			} else {
				u = next_int(p + 1, n), v = next_int(p + 1, n);
			}
			swap(a[u], a[v]);
		}
	}
	print(n);
}

int main() {
	freopen("input.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	// small samples
	for (int runs = 0; runs < 100; runs++) generate(100, 1000);
	for (int runs = 0; runs < 100; runs++) generate(100, 10000);
	for (int runs = 0; runs < 100; runs++) generate(100, 100000);
	for (int runs = 0; runs < 200; runs++) generate(100, 1000000000);
	// medium samples
	for (int runs = 0; runs < 30; runs++) generate_large(runs / 10);
	// big random samples
	for (int runs = 1; runs <= 5; runs++) {
		int n = next_int(1, 300000);
		for (int i = 1; i <= n; i++) a[i] = next_int(1, 1e9);
		for (int i = 1; i <= n; i++) b[i] = next_int(1, 1e9);
		print(n);
	}
	// good and bad mixed
	{
		long long cur = 0, minc = 0;
		for (int i = 1; i <= 100000; i++) {
			a[i] = cur + minc + next_int(1, 10);
			b[i] = a[i] + next_int(1, 10);
			minc = a[i] - cur;
			cur += b[i] - a[i];
		}
		for (int i = 100001; i <= 110000; i++) {
			a[i] = next_int(3e6, 4e6);
			b[i] = next_int(3e6, 4e6);
			if (a[i] > b[i]) swap(a[i], b[i]);
		}
		for (int i = 110001; i <= 120000; i++) {
			a[i] = next_int(1e7, 1e8);
			b[i] = next_int(1e7, 1e8);
			if (a[i] > b[i]) swap(a[i], b[i]);
		}
		for (int i = 110001; i <= 150000; i++) {
			a[i] = next_int(1e8, 1e9);
			b[i] = next_int(1e8, 1e9);
			if (a[i] > b[i]) swap(a[i], b[i]);
		}
		for (int i = 150001; i <= 250000; i++) {
			a[i] = next_int(2e5, 1e9);
			b[i] = a[i] - next_int(1, 100000);
		}
		for (int i = 250001; i <= 300000; i++) {
			a[i] = i - 250000 + 1;
			b[i] = a[i] - 1;
		}
		print(300000);
	}
	// only good monsters
	{
		long long cur = 0, minc = 0;
		for (int i = 1; i <= 300000; i++) {
			a[i] = cur + minc + next_int(1, 10);
			b[i] = a[i] + next_int(1, 10);
			minc = a[i] - cur;
			cur += b[i] - a[i];
		}
		print(300000);
	}
	// only bad monsters
	{
		for (int i = 1; i <= 300000; i++) {
			a[i] = next_int(1, 1e9);
			b[i] = next_int(1, 1e9);
			if (a[i] < b[i]) swap(a[i], b[i]);
		}
		print(300000);
	}
	// extreme case
	{
		for (int i = 1; i <= 300000; i++) {
			a[i] = 1e9;
			b[i] = 1;
		}
		print(300000);
	}
	return 0;
}

