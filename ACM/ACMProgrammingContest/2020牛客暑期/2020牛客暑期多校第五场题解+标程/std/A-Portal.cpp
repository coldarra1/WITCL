#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const int K = 610;
const int N = 310;
int _w;

int n, m, k, a[K];
ll g[N][N];

ll f[K][N];

void solve() {
	memset(f, 0x3f, sizeof f);
	f[0][1] = 0;
	for( int i = 0; i < k; ++i ) {
		for( int j = 1; j <= n; ++j ) {
			if( f[i][j] != INFLL ) {
				f[i+1][j] = min( f[i+1][j], f[i][j] + g[a[i]][a[i+1]] );
				for( int p = 1; p <= n; ++p ) {
					f[i+1][p] = min( f[i+1][p], f[i][j] + g[a[i]][p] + g[p][a[i+1]] );
					f[i+1][p] = min( f[i+1][p], f[i][j] + g[a[i]][p] + g[j][a[i+1]] );
					f[i+1][p] = min( f[i+1][p], f[i][j] + g[j][p] + g[p][a[i+1]] );
				}
			}
		}
	}
	ll ans = INFLL;
	for( int i = 1; i <= n; ++i )
		ans = min(ans, f[k][i]);
	printf( "%lld\n", ans );
}

int main() {
	_w = scanf( "%d%d%d", &n, &m, &k );
	memset(g, 0x3f, sizeof g);
	for( int i = 0; i < m; ++i ) {
		int u, v, w;
		_w = scanf( "%d%d%d", &u, &v, &w );
		g[u][v] = min( g[u][v], (ll)w );
		g[v][u] = min( g[v][u], (ll)w );
	}
	for( int i = 1; i <= n; ++i )
		g[i][i] = 0;
	for( int k = 1; k <= n; ++k )
		for( int i = 1; i <= n; ++i )
			for( int j = 1; j <= n; ++j )
				g[i][j] = min( g[i][j], g[i][k] + g[k][j] );
	k *= 2;
	for( int i = 1; i <= k; ++i )
		_w = scanf( "%d", a+i );
	a[0] = 1;
	solve();
	return 0;
}
