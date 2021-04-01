#include <bits/stdc++.h>
using namespace std;

#define FI(n) FastIO::read(n)
#define FO(n) FastIO::write(n)
#define Flush FastIO::Fflush()

namespace FastIO {
	const int SIZE = 1 << 16;
	char buf[SIZE], obuf[SIZE], str[60];
	int bi = SIZE, bn = SIZE, opt;
	double D[] = {0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001, 0.0000001, 0.00000001, 0.000000001, 0.0000000001};
	int read(char *s) {
		while (bn) {
			for (; bi < bn && buf[bi] <= ' '; bi++);
			if (bi < bn) break;
			bn = fread(buf, 1, SIZE, stdin);
			bi = 0;
		}
		int sn = 0;
		while (bn) {
			for (; bi < bn && buf[bi] > ' '; bi++) s[sn++] = buf[bi];
			if (bi < bn) break;
			bn = fread(buf, 1, SIZE, stdin);
			bi = 0;
		}
		s[sn] = 0;
		return sn;
	}
	bool read(int& x) {
		int n = read(str), bf = 0;
		if (!n) return 0;
		int i = 0; if (str[i] == '-') bf = 1, i++; else if (str[i] == '+') i++;
		for (x = 0; i < n; i++) x = x * 10 + str[i] - '0';
		if (bf) x = -x;
		return 1;
	}
	bool read(long long& x) {
		int n = read(str), bf;
		if (!n) return 0;
		int i = 0; if (str[i] == '-') bf = -1, i++; else bf = 1;
		for (x = 0; i < n; i++) x = x * 10 + str[i] - '0';
		if (bf < 0) x = -x;
		return 1;
	}
	void write(int x) {
		if (x == 0) obuf[opt++] = '0';
		else {
			if (x < 0) obuf[opt++] = '-', x = -x;
			int sn = 0;
			while (x) str[sn++] = x % 10 + '0', x /= 10;
			for (int i = sn - 1; i >= 0; i--) obuf[opt++] = str[i];
		}
		if (opt >= (SIZE >> 1)) {
			fwrite(obuf, 1, opt, stdout);
			opt = 0;
		}
	}
	void write(long long x) {
		if (x == 0) obuf[opt++] = '0';
		else {
			if (x < 0) obuf[opt++] = '-', x = -x;
			int sn = 0;
			while (x) str[sn++] = x % 10 + '0', x /= 10;
			for (int i = sn - 1; i >= 0; i--) obuf[opt++] = str[i];
		}
		if (opt >= (SIZE >> 1)) {
			fwrite(obuf, 1, opt, stdout);
			opt = 0;
		}
	}
	void write(unsigned long long x) {
		if (x == 0) obuf[opt++] = '0';
		else {
			int sn = 0;
			while (x) str[sn++] = x % 10 + '0', x /= 10;
			for (int i = sn - 1; i >= 0; i--) obuf[opt++] = str[i];
		}
		if (opt >= (SIZE >> 1)) {
			fwrite(obuf, 1, opt, stdout);
			opt = 0;
		}
	}
	void write(char x) {
		obuf[opt++] = x;
		if (opt >= (SIZE >> 1)) {
			fwrite(obuf, 1, opt, stdout);
			opt = 0;
		}
	}
	void Fflush() { if (opt) fwrite(obuf, 1, opt, stdout); opt = 0;}
};

const int N = 110000;
const int M = 350;

int A[N];
vector<int> con[N], adj[N];

struct Query {
	int type, u, x;
	Query(int type = 0, int u = 0, int x = 0) : type(type), u(u), x(x) {}
} Q[N];

int Array[N * M * 2], hello[N * M * 2];
int *BIT[N], *frq[N], lim[N];

inline void add(int id, int u, int x) {
	for (int i = u; i <= lim[id]; i += i & -i) BIT[id][i] += x;
}

inline int get(int id, int u) {
	int ret = 0;
	for (int i = u; i > 0; i -= i & -i) ret += BIT[id][i];
	return ret;
}

inline int get_lower_bound(int id, int s) {
	int ret = 0;
	for (int i = 31 - __builtin_clz(lim[id]); i >= 0; i--) {
		ret ^= 1<<i;
		if (ret > lim[id]) {
			ret ^= 1<<i;
			continue;
		}
		s -= BIT[id][ret];
		if (s <= 0) {
			s += BIT[id][ret];
			ret ^= 1<<i;
		}
	}
	return ++ret;
}

int main() {
	int tcase; FI(tcase);
	while (tcase--) {
		int n, m; FI(n), FI(m);
		for (int i = 1; i <= n; i++) FI(A[i]);
		for (int i = 0; i < m; i++) {
			int u, v; FI(u), FI(v);
			con[u].push_back(v), con[v].push_back(u);
		}
		for (int i = 1; i <= n; i++) {
			for (int v : con[i]) {
				if (con[v].size() >= M) adj[i].push_back(v);
			}
		}
		int q; FI(q);
		for (int i = 0; i < q; i++) {
			FI(Q[i].type), FI(Q[i].u);
			if (Q[i].type == 1) {
				FI(Q[i].x);
			}
		}
		for (int i = 1; i <= n; i++) lim[i] = con[i].size() + 1;
		int *p = Array, *qq = hello;
		for (int i = 1; i <= n; i++) {
			BIT[i] = p, p += lim[i] + 1;
			frq[i] = qq, qq += lim[i] + 1;
		}
		for (int i = 1; i <= n; i++) for (int j = 1; j <= lim[i]; j++) add(i, j, 1);
		for (int i = 1; i <= n; i++) if (con[i].size() < M) {
			for (int v : con[i]) {
				int val = A[i];
				if (val <= lim[v]) {
					if (!frq[v][val]) add(v, val + 1, -1);
					frq[v][val]++;
				}
			}
		}
		for (int i = 0; i < q; i++) {
			if (Q[i].type == 1) {
				if (con[Q[i].u].size() < M) {
					int val = A[Q[i].u];
					for (int v : con[Q[i].u]) {
						if (val <= lim[v]) {
							frq[v][val]--;
							if (!frq[v][val]) add(v, val + 1, 1);
						}
						if (Q[i].x <= lim[v]) {
							if (!frq[v][Q[i].x]) add(v, Q[i].x + 1, -1);
							frq[v][Q[i].x]++;
						}
					}
					A[Q[i].u] = Q[i].x;
				} else {
					A[Q[i].u] = Q[i].x;
				}
			} else {
				for (int v : adj[Q[i].u]) {
					if (A[v] <= lim[Q[i].u]) {
						if (!frq[Q[i].u][A[v]]) add(Q[i].u, A[v] + 1, -1);
						frq[Q[i].u][A[v]]++;
					}
				}
				FO(get_lower_bound(Q[i].u, 1) - 1), FO('\n');
				for (int v : adj[Q[i].u]) {
					if (A[v] <= lim[Q[i].u]) {
						frq[Q[i].u][A[v]]--;
						if (!frq[Q[i].u][A[v]]) add(Q[i].u, A[v] + 1, 1);
					}
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			con[i].clear(), adj[i].clear();
			for (int j = 0; j <= lim[i]; j++) BIT[i][j] = frq[i][j] = 0;
			lim[i] = 0;
		}
	}
	Flush;
	return 0;
}
