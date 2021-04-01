#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 100010;
const int B = 1e6;
int _w;

int n, p[N];
map<int,int> fac;

int solve( int pos ) {
	int cnt = 0;
	while( p[pos] ) {
		int nxt = p[pos];
		p[pos] = 0;
		pos = nxt;
		++cnt;
	}
	return cnt;
}

void factor( int x ) {
	for( int i = 2; i*i <= x; ++i )
		if( x % i == 0 ) {
			int cnt = 0;
			while( x % i == 0 )
				x /= i, ++cnt;
			fac[i] = max( fac[i], cnt );
		}
	if( x != 1 )
		fac[x] = max( fac[x], 1 );
}

int num[N], len;

void multiply( int x ) {
	int c = 0;
	for( int i = 0; i < len; ++i ) {
		ll tmp = (ll)x * num[i] + c;
		num[i] = int(tmp % B);
		c = int(tmp / B);
	}
	if( c ) num[len++] = c;
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d", p+i );
	for( int i = 1; i <= n; ++i )
		if( p[i] )
			factor( solve(i) );
	num[0] = 1, len = 1;
	for( auto it = fac.begin(); it != fac.end(); ++it ) {
		int now = 1;
		while( it->second-- )
			now *= it->first;
		multiply(now);
	}
	for( int i = len-1; i >= 0; --i ) {
		if( i == len-1 ) printf( "%d", num[i] );
		else printf( "%06d", num[i] );
	}
	puts("");
	return 0;
}
