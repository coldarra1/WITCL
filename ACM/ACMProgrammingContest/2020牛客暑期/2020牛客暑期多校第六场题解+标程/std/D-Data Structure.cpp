#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <string.h>
#define MAXN 200010
#define LIM 60

using namespace std;

int n , m , rt , size[ MAXN << 1 ] , fa[ MAXN ] , now;
int a[ MAXN ] , b[ MAXN ][4] , l[ MAXN ] , r[ MAXN ] , tot;

vector < int > linker[ MAXN ] , ext[ MAXN ];

inline void addedge( int x , int y )
{
	linker[x].push_back( y );
	linker[y].push_back( x );
}

#define cur linker[x][i]

void dfs1( int x )
{
	size[x] = 1;
	for( int i = 0 ; i < linker[x].size() ; i++ )
		if( cur != fa[x] )
		{
			fa[ cur ] = x;
			dfs1( cur ) , size[x] += size[ cur ];
		}
}

void dfs2( int x )
{
	a[ l[x] = ++tot ] = x;
	for( int i = 0 ; i < linker[x].size() ; i++ )
		if( cur != fa[x] )
			dfs2( cur );
	r[x] = tot;
}

inline bool cmp1( const int & a , const int & b )
{
	return size[a] > size[b];
}

struct ask
{
	int l , r , x , pos;
	ask( int l , int r , int x , int pos ) : l( l ) , r( r ) , x( x ) , pos( pos ) {}
	ask() {}
} q[ MAXN ];

vector < ask > v[ MAXN ];

int block , cnt , pre_ans[ MAXN ];
long long ans[ MAXN ];
bool have_light[ MAXN ];

#define belong( i ) ( ( i - 1 ) / block + 1 )

inline bool cmp2( const ask & a , const ask & b )
{
	return belong( a.l ) ^ belong( b.l ) ? belong( a.l ) < belong( b.l ) : belong( a.l ) & 1 ? a.r < b.r : a.r > b.r;
}

inline void insert( int x )
{
	if( b[x][0] )
	{
		pre_ans[ b[x][2] ] += size[ b[x][0] ]++;
		if( b[x][1] )
			pre_ans[ b[x][3] ] += size[ b[x][1] ]++;
	}
}

inline void erase( int x )
{
	if( b[x][0] )
	{
		pre_ans[ b[x][2] ] -= --size[ b[x][0] ];
		if( b[x][1] )
			pre_ans[ b[x][3] ] -= --size[ b[x][1] ];
	}
}

inline void addquery( int l , int r , int x , int pos )
{
	if( have_light[x] )
		q[ ++cnt ] = ask( l , r , x , pos );
	v[x].push_back( ask( l , r , -1 , pos ) );
}

#define find( x ) ( num1[x] + num2[ ( x ) >> 9 ] )

int num1[ MAXN + 512 ] , num2[ MAXN >> 9 ];

inline void modify( register int x )
{
	while( x >> 9 == x - 1 >> 9 ) num1[ x++ ]++;
	x >>= 9;
	while( x <= n >> 9 ) num2[ x++ ]++;
}

void dfs3( int x )
{
	if( b[x][0] ) b[x][1] = cnt , b[x][3] = now;
	else b[x][0] = cnt , b[x][2] = now;
	for( int i = 0 ; i < linker[x].size() ; i++ )
		if( cur != fa[x] )
			dfs3( cur );
}

struct io
{
	char ibuf[1 << 23] , * s , obuf[1 << 22] , * t;
	int a[24];
	io() : t( obuf )
	{
		fread( s = ibuf , 1 , 1 << 23 , stdin );
	}
	~io()
	{
		fwrite( obuf , 1 , t - obuf , stdout );
	}
	inline int read()
	{
		register int u = 0;
		while( * s < 48 )
			s++;
		while( * s > 32 )
			u = u * 10 + * s++ - 48;
		return u;
	}
	template < class T >
	inline void print( T u , int v )
	{
		print( u );
		* t++ = v;
	}
	template < class T >
	inline void print( register T u )
	{
		static int * q = a;
		if( !u ) * t++ = 48;
		else
		{
			if( u < 0 )
				* t++ = 45 , u *= -1;
			while( u ) * q++ = u % 10 + 48 , u /= 10;
			while( q != a )
				* t++ = * --q;
		}
	}
} ip;

#define read ip.read
#define print ip.print

int main()
{
	n = read() , m = read() , rt = read();
	for( register int i = 1 ; i <= n - 1 ; i++ )
		addedge( read() , read() );
	dfs1( rt );
	for( int i = 1 ; i <= n ; i++ )
		sort( linker[i].begin() , linker[i].end() , cmp1 );
	dfs2( rt );
	for( int x = 1 ; x <= n ; x++ )
		for( int i = 0 ; i < linker[x].size() ; i++ )
			if( cur != fa[x] )
			{
				if( i >= LIM )
				{
					cnt++;
					now = x;
					have_light[x] = 1;
					dfs3( cur );
				}
				if( i <= LIM )
					ext[ l[ cur ] - 1 ].push_back( x );
				if( i + 1 == linker[x].size() )
				{
					if( i <= LIM )
						ext[ r[ cur ] ].push_back( x );
					ext[ r[ cur ] ].push_back( -x );
				}
			}
	cnt = 0;
	for( int i = 1 ; i <= m ; i++ )
	{
		int l = read() , r = read() , x = read();
		addquery( l , r , x , i );
	}
	block = n / sqrt( cnt * 2 / 3 + 1 );
	sort( q + 1 , q + cnt + 1 , cmp2 );
	memset( size , 0 , sizeof( size ) );
	for( int i = 1 , l = 1 , r = 0 ; i <= cnt ; i++ )
	{
		while( l > q[i].l ) insert( --l );
		while( r < q[i].r ) insert( ++r );
		while( l < q[i].l ) erase( l++ );
		while( r > q[i].r ) erase( r-- );
		ans[ q[i].pos ] -= pre_ans[ q[i].x ];
	}
	//扫描线扫dfs序，数据结构维护点编号 
	memset( pre_ans , 0 , sizeof( pre_ans ) );
	for( int i = 1 ; i <= n ; i++ )
	{
		modify( a[i] );
		for( int j = 0 ; j < ext[i].size() ; j++ )
		{
			int x = ext[i][j] , f = 0;
			if( x < 0 ) x *= -1 , f = 1;
			for( int k = 0 ; k < v[x].size() ; k++ )
			{
				int y = find( v[x][k].r ) - find( v[x][k].l - 1 );
				if( v[x][k].x != -1 )
					if( !f )
						ans[ v[x][k].pos ] -= ( y - v[x][k].x ) * 1ll * ( y - v[x][k].x - 1 ) >> 1;
					else
						;
				else
					pre_ans[ v[x][k].pos ] = -y; 
				v[x][k].x = y;
			}
		}
	}
	for( int i = 1 ; i <= n ; i++ )
		for( int j = 0 ; j < v[i].size() ; j++ )
			pre_ans[ v[i][j].pos ] += max( 0 , v[i][j].x ) + ( v[i][j].l <= i && i <= v[i][j].r );
	for( int i = 1 ; i <= m ; i++ )
		print( ans[i] + ( pre_ans[i] * 1ll * ( pre_ans[i] - 1 ) >> 1 ) , 10 );
	return 0;
}
