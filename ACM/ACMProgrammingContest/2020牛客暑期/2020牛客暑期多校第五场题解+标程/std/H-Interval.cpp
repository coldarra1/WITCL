#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int N = 100010;
const int B = 30;
int _w;

int n, q, a[N];
vector<int> rbound[N];

int bit[N];

void init_bit( int b ) {
	for( int i = 1; i <= n; ++i )
		bit[i] = bool(a[i] & (1<<b));
	int zero = n;
	for( int i = n; i >= 1; --i ) {
		if( bit[i] == 0 ) zero = i;
		rbound[i].push_back(zero);
	}
}

struct Point {
	int x, y, w;
	bool operator<( const Point &rhs ) const {
		return x < rhs.x;
	}
};

map<int,vector<pii> > rng;
vector<Point> points;

namespace PSGT {
	struct Node {
		Node *lc, *rc;
		int sum;
	};
	Node *nul, *rt[N];
	
	void init() {
		nul = new Node;
		nul->lc = nul->rc = nul;
		nul->sum = 0;
		rt[0] = nul;
	}
	Node *get_rt( int x ) {
		if( rt[x] ) return rt[x];
		else return rt[x] = get_rt(x-1);
	}
	Node *_add( Node *o, int L, int R, int pos, int val ) {
		Node *nod = new Node(*o);
		if( L == R ) {
			nod->sum += val;
			return nod;
		} else {
			int M = (L+R)/2;
			if( pos <= M ) nod->lc = _add(nod->lc, L, M, pos, val);
			else nod->rc = _add(nod->rc, M+1, R, pos, val);
			nod->sum = nod->lc->sum + nod->rc->sum;
			return nod;
		}
	}
	void build() {
		init();
		sort(points.begin(), points.end());
		for( Point now : points ) {
			rt[now.x] = _add( get_rt(now.x), 1, n, now.y, now.w );
		}
	}
	int _query( Node *o, int L, int R, int ql, int qr ) {
		if( L >= ql && R <= qr ) {
			return o->sum;
		} else {
			int M = (L+R)/2, ans = 0;
			if( ql <= M ) ans += _query(o->lc, L, M, ql, qr);
			if( qr > M ) ans += _query(o->rc, M+1, R, ql, qr);
			return ans;
		}
	}
	int query( int version, int L, int R ) {
		return _query( get_rt(version), 1, n, L, R );
	}
}

bool contain( pii a, pii b ) {
	return a.first <= b.first && a.second >= b.second;
}

void init() {
	for( int i = 0; i < B; ++i )
		init_bit(i);
	for( int i = 1; i <= n; ++i ) {
		vector<int> &rb = rbound[i];
		rb.push_back(i);
		sort(rb.begin(), rb.end());
		int sz = int(unique(rb.begin(), rb.end()) - rb.begin());
		rb.resize(sz);
		int now = (1<<B)-1;
		for( int R : rb ) {
			now &= a[R];
			rng[now].push_back( pii(i, R) );
		}
	}
	for( auto it = rng.begin(); it != rng.end(); ++it ) {
		int num = it->first;
		vector<pii> &vec = it->second;
		sort(vec.begin(), vec.end());
		vector<pii> tmp;
		for( pii point : vec ) {
			while( !tmp.empty() && contain(tmp.back(), point) )
				tmp.pop_back();
			tmp.push_back(point);
		}
		int sz = (int)tmp.size();
		for( int i = 0; i < sz; ++i )
			points.push_back( (Point){tmp[i].first, tmp[i].second, 1} );
		for( int i = 1; i < sz; ++i )
			points.push_back( (Point){tmp[i-1].first, tmp[i].second, -1} );
	}
	PSGT::build();
}

int solve( int l, int r ) {
	return PSGT::query(r, l, r) - PSGT::query(l-1, l, r);
}

int main() {
	_w = scanf( "%d", &n );
	for( int i = 1; i <= n; ++i )
		_w = scanf( "%d", a+i );
	init();
	_w = scanf( "%d", &q );
	int lastans = 0;
	while( q-- ) {
		int l, r;
		_w = scanf( "%d%d", &l, &r );
		l = (l ^ lastans) % n + 1;
		r = (r ^ lastans) % n + 1;
		if( l > r ) swap(l, r);
		printf( "%d\n", lastans = solve(l, r) );
	}
	return 0;
}