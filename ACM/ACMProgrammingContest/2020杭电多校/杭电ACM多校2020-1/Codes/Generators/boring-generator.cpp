#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N = 220000;

long long a[N];
int d[N];

template<typename T>
inline T next_int(T l, T r) {
	return uniform_int_distribution<T>(l, r)(rng);
}

long long stupid_greedy(int n, const vector<long long> &a, const vector<int> &d, const function<long long(pair<long long, int>)> &eval) {
	vector<pair<long long, int>> p(n + 1);
	for (int i = 1; i <= n; i++) p[i] = {a[i], d[i]};
	sort(p.begin() + 1, p.end());
	set<pair<long long, int>> S;
	long long curt = 0, ans = 0;
	int sz = 0, i = 1;
	while (sz < n) {
		if (S.empty()) curt = max(curt, p[i].first);
		while (i <= n && p[i].first <= curt) S.emplace(eval(p[i]), i), i++;
		auto it = S.begin();
		int k = it->second;
		S.erase(it);
		ans = max(ans, curt - p[k].first);
		curt += p[k].second;
		sz++;
	}
	return ans;
}

long long simple_greedy(int n, const vector<long long> &a, const vector<int> &d, const function<bool(pair<long long, int>, pair<long long, int>)> &comp) {
	vector<pair<long long, int>> p(n + 1);
	for (int i = 1; i <= n; i++) p[i] = {a[i], d[i]};
	sort(p.begin() + 1, p.end(), comp);
	long long curt = 0, ans = 0;
	for (int i = 1; i <= n; i++) {
		curt = max(curt, p[i].first);
		ans = max(ans, curt - p[i].first);
		curt += p[i].second;
	}
	return ans;
}

bool compare_before(pair<long long, int> lhs, pair<long long, int> rhs) {
	int Lflag = lhs.first <= rhs.first;
	int Rflag = lhs.second + lhs.first <= rhs.second + rhs.first;
	return Lflag != Rflag ? rhs.first - lhs.first > lhs.second - rhs.second - (rhs.first - lhs.first) : lhs.first + lhs.second < rhs.first + rhs.second;
}

bool compare_after(pair<long long, int> lhs, pair<long long, int> rhs) {
	return lhs.first + lhs.second < rhs.first + rhs.second;
}

long long slow_greedy(int n, const vector<long long> &a, const vector<int> &d) {
	vector<pair<long long, int>> p(n + 1);
	for (int i = 1; i <= n; i++) p[i] = {a[i], d[i]};
	sort(p.begin() + 1, p.end());
	auto compare = [&](int u, int v, long long t) {
		if (t > max(p[u].first + p[u].second, p[v].first + p[v].second)) {
			return compare_after(p[u], p[v]);
		} else {
			return compare_before(p[u], p[v]);
		}
	};
	long long curt = 0, ans = 0;
	int sz = 0;
	vector<int> used(n + 1);
	while (sz < n) {
		int u = 0;
		for (int i = 1; i <= n; i++) {
			if (used[i]) continue;
			if (u == 0 || compare(i, u, curt)) u = i;
		}
		curt = max(curt, p[u].first);
		used[u] = 1;
		ans = max(ans, curt - p[u].first);
		curt += p[u].second;
		sz++;
	}
	return ans;
}

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

long long solution_with_a_bug(int n, const vector<long long> &T, const vector<int> &D) {
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
				if (u == i + 1 || now - s[u - 1] > cur + a[i].second) dp[i] = max(dp[i], now - s[u - 1] + s[i - 1]);
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

long long wrong_dp(int n, const vector<long long> &T, const vector<int> &D) {
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
		int qn = 0, k = n + 1;
		for (int i = n, j = n; i > 0; i--) {
			while (j > i && a[j].first >= a[i].first + t) j--;
			dp[i] = -inf;
			int optj = 0;
			for (int j = i + 1; j <= k; j++) {
				long long cur = (j == i + 1 ? a[i].first - s[i] : bmax(i + 1, j - 1));
				long long now = min(dp[j], a[i].first + a[i].second + t);
				if (now - s[j - 1] >= cur + a[i].second) {
					if (dp[i] < now - s[j - 1] + s[i - 1]) {
						optj = j;
					}
					dp[i] = max(dp[i], now - s[j - 1] + s[i - 1]);
				}
				if (j == n + 1 || a[j].first + a[j].second >= a[i].first + a[i].second || a[i].first + a[i].second + t < dp[j]) break;
			}
			k = optj;
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

long long brute_force_with_heuristic(int n, const vector<long long> &T, const vector<int> &D) {
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
	auto check = [&](long long t) {
		dp[n + 1] = inf;
		for (int i = n, j = n; i > 0; i--) {
			while (j > i && a[j].first >= a[i].first + t) j--;
			dp[i] = -inf;
			for (int j = i + 1; j <= n + 1; j++) {
				long long cur = (j == i + 1 ? a[i].first - s[i] : bmax(i + 1, j - 1));
				long long now = min(dp[j], a[i].first + a[i].second + t);
				if (now - s[j - 1] >= cur + a[i].second) dp[i] = max(dp[i], now - s[j - 1] + s[i - 1]);
				if (j == n + 1 || a[j].first + a[j].second >= a[i].first + a[i].second || a[i].first + a[i].second + t < dp[j]) break;
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
	freopen("data.in", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	auto print = [&](int n) {
		vector<int> id(n + 1);
		for (int i = 1; i <= n; i++) id[i] = i;
		random_shuffle(id.begin() + 1, id.end());
		cout << n << "\n";
		for (int i = 1; i <= n; i++) cout << a[id[i]] << " \n"[i == n];
		for (int i = 1; i <= n; i++) cout << d[id[i]] << " \n"[i == n];
	};
	auto make_some_wrong_solution_fail = [&](int n, int flag = false) {
		vector<long long> a(n + 1);
		vector<int> d(n + 1);
		int cnt = 0;
		while (1) {
			cnt++;
			for (int i = 1; i <= n; i++) a[i] = next_int(1, 10000);
			for (int i = 1; i <= n; i++) d[i] = next_int(1, 300);
			long long ans = correct_solution(n, a, d);
			long long ret = min(stupid_greedy(n, a, d, [&](pair<long long, int> x) {
				return x.second;
			}), stupid_greedy(n, a, d, [&](pair<long long, int> x) {
				return x.first;
			}));
			ret = min(ret, simple_greedy(n, a, d, compare_after));
			ret = min(ret, simple_greedy(n, a, d, compare_before));
			ret = min(ret, slow_greedy(n, a, d));
			if (flag) ret = min(ret, solution_with_a_bug(n, a, d));
			ret = min(ret, wrong_dp(n, a, d));
			assert(ans <= ret);
			if (ans != ret) {
				for (int i = 1; i <= n; i++) ::a[i] = a[i];
				for (int i = 1; i <= n; i++) ::d[i] = d[i];
				print(n);
				return;
			}
		}
	};
	// small samples
	for (int runs = 0; runs < 200; runs++) {
		int n = next_int(1, 30);
		for (int i = 1; i <= n; i++) {
			a[i] = next_int(1, 100);
			d[i] = next_int(1, 100);
		}
		print(n);
	}
	for (int runs = 0; runs < 200; runs++) {
		int n = next_int(1, 30);
		for (int i = 1; i <= n; i++) {
			a[i] = next_int(1, 100);
			d[i] = next_int(1, 10);
		}
		print(n);
	}
	// catch wrong greedy
	for (int i = 0; i < 500; i++) {
		make_some_wrong_solution_fail(next_int(100, 200), 0);
	}
	for (int i = 0; i < 100; i++) {
		make_some_wrong_solution_fail(next_int(10, 20), 1);
	}
	// make quadratic dp with heuristic time limit exceeded
	{
		int n = 100000;
		for (int i = 1; i <= n; i++) a[i] = i;
		for (int i = 1; i <= n; i++) d[i] = 1e9 - 2 * i;
		print(n);
	}
	// the answer is zero
	{
		int n = 100;
		for (int i = 1; i <= n; i++) a[i] = i;
		for (int i = 1; i <= n; i++) d[i] = 1;
		print(n);
	}
	// the answer is maximum
	{
		int n = 200000;
		for (int i = 1; i <= n; i++) a[i] = 1;
		for (int i = 1; i <= n; i++) d[i] = 1e9;
		print(n);
	}
	// extreme case
	{
		int n = 200000;
		for (int i = 1; i <= n; i++) a[i] = 2e14;
		for (int i = 1; i <= n; i++) d[i] = 1e9;
		print(n);
	}
	// small answers
	for (int runs = 0; runs < 5; runs++) {
		int n = next_int(1, 100);
		for (int i = 1; i <= n; i++) a[i] = next_int(1, 100);
		for (int i = 1; i <= n; i++) d[i] = next_int(1, 100);
		for (int i = 1; i <= n; i++) a[i] = max(a[i], next_int(a[i - 1] + d[i - 1], a[i - 1] + d[i - 1] + 1000));
		print(n);
	}
	// big random samples
	for (int runs = 0; runs < 5; runs++) {
		int n = next_int(1, 200000);
		for (int i = 1; i <= n; i++) {
			a[i] = next_int(1LL, 200000000000000LL);
			d[i] = next_int(1, 1000000000);
		}
		print(n);
	}
	// medium random samples
	for (int runs = 0; runs < 10; runs++) {
		int n = next_int(10000, 20000);
		for (int i = 1; i <= n; i++) {
			a[i] = next_int(1LL, 1000000000LL * n);
			d[i] = next_int(1, 1000000000);
		}
		print(n);
	}
	// make stairs
	for (int runs = 0; runs < 5; runs++) {
		int num_stairs = next_int(1, 10);
		long long curt = 0;
		int n = 0;
		for (int i = 1; i <= num_stairs; i++) {
			int cnt = next_int(10000, 20000);
			for (int j = 1; j <= cnt; j++) {
				a[n + j] = curt + j;
				d[n + j] = 2 * cnt + 1 - 2 * j;
			}
			n += cnt;
			for (int j = 1; j <= cnt; j++) {
				curt += 2 * cnt + 1 - j;
			}
			curt += next_int(1, 10000);
		}
		print(n);
	}
	// small and large mixed
	for (int runs = 0; runs < 30; runs++) {
		int n = next_int(20, 120), m = n / 3;
		for (int i = 1; i <= n; i++) a[i] = i <= m ? next_int(1, 1000000000) : next_int(1, 1000);
		for (int i = 1; i <= n; i++) d[i] = i <= m ? next_int(1, 1000000000) : next_int(1, 100);
		print(n);
	}
	// length value is power of 2
	for (int runs = 0; runs < 5; runs++) {
		int n = next_int(10000, 20000);
		for (int i = 1; i <= n; i++) a[i] = next_int(1, 1000000000);
		for (int i = 1; i <= n; i++) d[i] = 1 << next_int(0, 20);
		print(n);
	}
	// some hand-made
	{
		int n = 100000;
		for (int i = 1; i <= n; i++) a[i] = i * 1000;
		for (int i = 1; i <= n; i++) d[i] = i <= n / 2 ? 2000 * (n / 2 + 1 - i) : 2e8 + 2000 * (n - i + 1);
		print(n);
	}
	{
		int n = 200000;
		set<int> S;
		for (int i = 1; i <= n; i++) {
			do {
				a[i] = next_int<int>(1, 1e9);
			} while (S.count(a[i]));
			S.insert(a[i]);
		}
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) d[i] = next_int(max<long long>(1, a[i] - a[i - 1] - 100), a[i] - a[i - 1]);
		for (int i = 2; i <= n; i++) a[i] -= min(a[i] - 1, next_int<long long>(20000, 30000));
		print(n);
	}
	// some small cases
	for (int runs = 0; runs < 50; runs++) {
		int n = 100;
		for (int i = 1; i <= n; i++) a[i] = next_int(1, 10000);
		for (int i = 1; i <= n; i++) d[i] = next_int(1, 500);
		print(n);
	}
	// some medium cases
	for (int runs = 0; runs < 5; runs++) {
		int n = next_int(20000, 30000);
		set<int> S;
		for (int i = 1; i <= n; i++) {
			do {
				a[i] = next_int<long long>(1, 1e9);
			} while (S.count(a[i]));
			S.insert(a[i]);
		}
		sort(a + 1, a + n + 1);
		int cnt = next_int(1, 20);
		vector<int> pos(cnt + 1);
		for (int i = 0; i < cnt; i++) pos[i] = next_int(1, n);
		pos.push_back(1);
		pos.push_back(n + 1);
		sort(pos.begin(), pos.end());
		pos.resize(unique(pos.begin(), pos.end()) - pos.begin());
		for (int i = 0; i + 1 < pos.size(); i++) reverse(a + pos[i], a + pos[i + 1]);
		for (int i = 1; i <= n; i++) d[i] = a[i];
		int cur = 1e9;
		for (int i = n; i > 0; i--) {
			cur = min(cur, d[i] - 1);
			a[i] = cur;
		}
		for (int i = 1; i <= n; i++) a[i] = next_int(max(1LL, a[i - 1]), a[i]);
		for (int i = 1; i <= n; i++) d[i] -= a[i];
		for (int i = 1; i < n; i++) assert(a[i] <= a[i + 1]);
		print(n);
	}
	// some large cases
	for (int runs = 0; runs < 2; runs++) {
		int n = next_int(50000, 100000);
		set<int> S;
		for (int i = 1; i <= n; i++) {
			do {
				a[i] = next_int<long long>(1, 1e9);
			} while (S.count(a[i]));
			S.insert(a[i]);
		}
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) d[i] = next_int(max(1LL, a[i] - a[i - 1] - 10000), a[i] - a[i - 1]);
		for (int i = 2; i <= n; i++) a[i] -= next_int(0LL, max(a[i] / 3, 0LL));
		print(n);
	}
	// other cases
	for (int runs = 0; runs < 2; runs++) {
		int n = next_int(100000, 200000);
		for (int i = 1; i <= n; i++) {
			int cnt = next_int(0, 9);
			d[i] = 1;
			for (int j = 0; j < cnt; j++) d[i] *= 10;
			a[i] = next_int(1, d[i]);
		}
		print(n);
	}
	return 0;
}
