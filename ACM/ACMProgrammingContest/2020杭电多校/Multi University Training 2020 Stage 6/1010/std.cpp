#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<utility>

using namespace std;

typedef long long ll;

const int mod = 998244353;
const int maxn = 100;
const int maxm = 1e4;

ll quickpow(ll x, ll y, ll p) {
	ll res = 1;
	while (y) {
		if (y & 1)res = res * x % p;
		x = x * x % p;
		y >>= 1;
	}
	return res % p;
}

ll Determinant(const vector<vector<int>>& A) {
	ll res = 1;
	int n = A.size(), cnt = 0;
	vector<vector<int>> B(n, vector<int>(n));
	for (int i = 0; i < n; ++i)for (int j = 0; j < n; ++j)B[i][j] = A[i][j];
	for (int i = 0; i < n; ++i) {
		int pivot = i;
		for (int j = i; j < n; ++j)if (abs(B[j][i]) > abs(B[pivot][i]))pivot = j;
		if (i != pivot) {
			swap(B[i], B[pivot]);
			cnt ^= 1;
		}
		if (B[i][i] == 0)return -1;
		ll val = quickpow(B[i][i], mod - 2, mod);
		for (int j = i + 1; j < n; ++j) {
			ll coe = B[j][i] * val % mod;
			for (int k = i; k < n; ++k)B[j][k] = (B[j][k] - 1ll * coe * B[i][k] % mod) % mod;
		}
	}
	for (int i = 0; i < n; ++i)res = res * B[i][i] % mod;
	if (cnt)res = -res;
	if (res < 0)res += mod;
	return res;
}

struct edge {
	edge(int _u = 0, int _v = 0, int _w = 0) {
		u = _u, v = _v, w = _w;
	}
	int u, v, w;
}e[maxm + 5];

int T, n, m, arr[maxn + 5][maxn + 5];
vector<vector<int>> vec;
ll sum, res;

int main()
{
	scanf("%d", &T);
	while (T--) {
		sum = res = 0;
		memset(arr, 0, sizeof(arr));
		vec.clear();
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= m; ++i)scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
		for (int i = 1, u, v; i <= m; ++i) {
			u = e[i].u, v = e[i].v;
			arr[u][u] += 1, arr[v][v] += 1;
			arr[u][v] -= 1, arr[v][u] -= 1;
		}
		for (int i = 1; i < n; ++i) {
			vec.push_back({});
			for (int j = 1; j < n; ++j)vec[i - 1].push_back(arr[i][j]);
		}
		sum = Determinant(vec);
		for (int i = 0; i < 30; ++i) {
			memset(arr, 0, sizeof(arr));
			vec.clear();
			for (int j = 1, u, v; j <= m; ++j) {
				u = e[j].u, v = e[j].v;
				if (e[j].w & (1 << i)) {
					arr[u][u] += 1, arr[v][v] += 1;
					arr[u][v] -= 1, arr[v][u] -= 1;
				}
			}
			for (int i = 1; i < n; ++i) {
				vec.push_back({});
				for (int j = 1; j < n; ++j)vec[i - 1].push_back(arr[i][j]);
			}
			ll ans = Determinant(vec);
			if (ans == -1)continue;
			res = (res + (1ll << i) * ans % mod) % mod;
		}
		res = res * quickpow(sum, mod - 2, mod) % mod;
		printf("%lld\n", res);
	}
	return 0;
}