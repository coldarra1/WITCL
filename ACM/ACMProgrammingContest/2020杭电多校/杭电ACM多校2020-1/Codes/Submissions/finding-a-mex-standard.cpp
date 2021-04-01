#include <bits/stdc++.h>
using namespace std;

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
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int tcase; cin >> tcase;
	while (tcase--) {
		int n, m; cin >> n >> m;
		for (int i = 1; i <= n; i++) cin >> A[i];
		for (int i = 0; i < m; i++) {
			int u, v; cin >> u >> v;
			con[u].push_back(v), con[v].push_back(u);
		}
		for (int i = 1; i <= n; i++) {
			for (int v : con[i]) {
				if (con[v].size() >= M) adj[i].push_back(v);
			}
		}
		
		int q; cin >> q;
		for (int i = 0; i < q; i++) {
			cin >> Q[i].type >> Q[i].u;
			if (Q[i].type == 1) {
				cin >> Q[i].x;
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
				
				cout << get_lower_bound(Q[i].u, 1) - 1 << "\n";
				
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
	
	return 0;
}
