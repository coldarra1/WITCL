#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <time.h>
#define MAXN 200010
#define block 700
#define ptnum 200
#define inf 1000000000000000000ll
#define INF 1000000000
#define update_res( res , x ) res > x ? res = x : 0

using namespace std;

int n , m , rt , a[ MAXN ] , d[ MAXN ] , fa[ MAXN ] , v[ MAXN ] , temp[ MAXN ] , cnt , A[ MAXN ];
bool not_leaf[ MAXN ];
long long dep[ MAXN ] , ans[ MAXN ] , la[ ptnum + 1 ][ MAXN ];

vector < int > linker[ MAXN ] , di[ MAXN ];

int belong[ MAXN ] , add[ MAXN ] , block_add[ MAXN / block + 10 ] , L[ MAXN / block + 10 ] , R[ MAXN / block + 10 ];
vector < int > B[ MAXN / block + 10 ];

inline void addedge( int x , int y , int z )
{
    linker[x].push_back( y );
    di[x].push_back( z );
}

#define cur linker[x][i]
#define dist di[x][i]

void dfs( int x )
{
    for( int i = 0 ; i < linker[x].size() ; i++ )
        if( cur != fa[x] )
            fa[ cur ] = x , dep[ cur ] = dep[x] + dist , dfs( cur );
}

#undef cur

struct value
{
    int a[ ptnum + 1 ] , tag; //最向上跑的长度，整体加 
    inline void set()
    {
        tag = 0; 
        for( int i = 1 ; i <= cnt ; i++ )
            a[i] = -INF;
    }    
    value()
    {
        set();
    }
    inline void update( int x , int y )
    {
        a[x] = max( a[x] , y );
    }
    inline void merge( const value & v , int t )
    {
        for( int i = 1 ; i <= cnt ; i++ )
            if( v.a[i] + t > a[i] )
                a[i] = v.a[i] + t;
    }
} C , D[ MAXN / block + 10 ];

struct Node
{
    int size;
    value v;
    Node * left , * right;
    Node( int s , value v , Node * a , Node * b ) : size( s ) , v( v ) , left( a ) , right( b )
    {
        v.set();
    }
} * root;

inline void update( Node * cur )
{
    if( cur -> left )
    {
        value * a = & cur -> left -> v , * b = & cur -> right -> v;
        int x = cur -> left -> v.tag , y = cur -> right -> v.tag;
        for( register int i = 1 ; i <= cnt ; i++ )
            cur -> v.a[i] = max( a -> a[i] + x , b -> a[i] + y );
    }
}

Node * build( int l , int r )
{
    if( l == r ) return new Node( 1 , D[l] , 0 , 0 );
    Node * left = build( l , l + r >> 1 ) , * right = build( ( l + r >> 1 ) + 1 , r );
    Node * cur = new Node( r - l + 1 , value() , left , right );
    update( cur );
    return cur;
}

void insert( int x , int a , int b , int t , Node * cur ) //单点插入 
{
    t += cur -> v.tag;
    if( cur -> size != 1 )
        x > cur -> left -> size ? insert( x - cur -> left -> size , a , b , t , cur -> right ) : insert( x , a , b , t , cur -> left ); 
    cur -> v.update( a , b - t );
}

void fix( int x , int t , Node * cur ) //单点修改 
{
    t += cur -> v.tag;
    if( cur -> size == 1 )
        for( int i = 1 ; i <= cnt ; i++ )
            cur -> v.a[i] = C.a[i] - t;
    else
    {
        x > cur -> left -> size ? fix( x - cur -> left -> size , t , cur -> right ) : fix( x , t , cur -> left );
        cur -> v.a[0] = 1; //延迟update的标记 
    }
}

void modify( int l , int r , Node * cur ) //区间加
{
    if( l > r ) return;
    if( cur -> size == r - l + 1 ) cur -> v.tag++;
    else
    {
        if( l > cur -> left -> size ) modify( l - cur -> left -> size , r - cur -> left -> size , cur -> right );
        else if( cur -> left -> size >= r ) modify( l , r , cur -> left );
        else modify( l , cur -> left -> size , cur -> left ) , modify( 1 , r - cur -> left -> size , cur -> right );
        cur -> v.a[0] = 1; //延迟update的标记 
    }
}

void update_all( Node * cur ) //延迟update
{
    if( cur -> v.a[0] )
    {
        update_all( cur -> left );
        update_all( cur -> right );
        update( cur );
        cur -> v.a[0] = 0; 
    }
}

void find( int l , int r , int t , Node * cur ) //区间信息
{
    if( l > r ) return;
    t += cur -> v.tag;
    if( cur -> size == r - l + 1 ) C.merge( cur -> v , t );
    else
        if( l > cur -> left -> size ) find( l - cur -> left -> size , r - cur -> left -> size , t , cur -> right );
        else if( cur -> left -> size >= r ) find( l , r , t , cur -> left );
        else find( l , cur -> left -> size , t , cur -> left ) , find( 1 , r - cur -> left -> size , t , cur -> right );
}

struct io
{
    char ibuf[40 << 20] , * s , obuf[1 << 23] , * t;
    int a[24];
    io() : t( obuf )
    {
        fread( s = ibuf , 1 , 40 << 20 , stdin );
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

inline void init_tree()
{
    fa[ rt ] = rt;
    memset( not_leaf , 0 , sizeof( not_leaf ) );
    for( int i = 1 ; i <= n ; i++ )
        not_leaf[ fa[i] ] = 1;
    cnt = 0;
    for( int i = 1 ; i <= n ; i++ )
        if( !not_leaf[i] ) //叶子 
            v[ ++cnt ] = i;
    memset( not_leaf , 0 , sizeof( not_leaf ) );
    while( 1 ) //剥叶子 
    {
        int tot = 0;
        for( int i = 1 ; i <= cnt ; i++ )
            if( !not_leaf[ fa[ v[i] ] ] )
                not_leaf[ fa[ v[i] ] ] = 1 , temp[ ++tot ] = fa[ v[i] ];
        cnt = tot;
        for( register int i = 1 ; i <= cnt ; i++ )
            v[i] = temp[i];
        if( cnt <= ptnum ) break;
    }
    if( v[ cnt ] == 0 ) v[ cnt ] = rt;
    memset( temp , 0 , sizeof( temp ) );
    for( int i = 1 ; i <= cnt ; i++ )
    {
        int tot = 0 , now = v[i];
        while( 1 )
        {
            if( !temp[ now ] ) //之前没标号的点 
            {
                temp[ now ] = i;
                d[ now ] = tot;
            }
            la[i][ tot++ ] = dep[ now ]; //k祖先深度 
            if( now == rt ) break;
            now = fa[ now ];
        }
        while( tot <= m )
            la[i][ tot++ ] = 0;
    }
}

inline void init_block()
{
    memset( L , 0 , sizeof( L ) );
    memset( R , 0 , sizeof( R ) );
    for( int i = 1 ; i <= n ; i++ )
        if( !L[ belong[i] ] )
            L[ belong[i] ] = i;
    for( int i = n ; i ; i-- )
        if( !R[ belong[i] ] )
            R[ belong[i] ] = i;
    for( int i = 1 ; i <= belong[n] ; i++ )
    {
        ans[i] = inf;
        D[i].set();
        B[i].clear();
    }
    for( int i = 1 ; i <= n ; i++ )
        if( temp[ a[i] ] ) //初始是上位点 
        {
            D[ belong[i] ].update( temp[ a[i] ] , d[ a[i] ] );
            A[i] = temp[ a[i] ];
            add[i] = d[ a[i] ];
        }
        else //初始是下位点
        {
            B[ belong[i] ].push_back( i );
            update_res( ans[ belong[i] ] , dep[ a[i] ] );
        }
    root = build( 1 , belong[n] );
}

int main()
{
    int t = read();
    while( t-- )
    {
        n = read() , m = read() , rt = read();
        memset( fa , 0 , sizeof( fa ) );
        memset( v , 0 , sizeof( v ) );
        memset( temp , 0 , sizeof( temp ) );
        memset( A , 0 , sizeof( A ) );
        memset( not_leaf , 0 , sizeof( not_leaf ) );
        memset( dep , 0 , sizeof( dep ) );
        memset( add , 0 , sizeof( add ) );
        memset( block_add , 0 , sizeof( block_add ) );
        for( register int i = 1 ; i <= n ; i++ ) linker[i].clear() , di[i].clear();
        for( int i = 2 ; i <= n ; i++ )
        {
            int x = read() , y = read() , z = read();
            addedge( x , y , z );
            addedge( y , x , z );
        }
        dfs( rt );
        for( int i = 1 ; i <= n ; i++ )
        {
            a[i] = read();
            belong[i] = ( i - 1 ) / block + 1;
        }
        init_tree();
        init_block();
        while( m-- )
        {
            int opt = read() , l = read() , r = read();
            if( opt == 1 )
            {
                int x = block_add[ belong[l] ];
                if( belong[l] == belong[r] )
                {
                    C.set();
                    for( register int i = l ; i <= r ; i++ ) //全部上位点加 
                        if( A[i] )
                            add[i]++;
                    for( int i = L[ belong[l] ] ; i <= R[ belong[r] ] ; i++ ) //块内重构插入线段树 
                        C.update( A[i] , add[i] + x );
                    fix( belong[l] , 0 , root );
                }
                else
                {
                    C.set();
                    for( register int i = l ; i <= R[ belong[l] ] ; i++ ) //左边上位点加 
                        if( A[i] )
                            add[i]++;
                    for( register int i = L[ belong[l] ] ; i <= R[ belong[l] ] ; i++ ) //左边块内重构插入线段树 
                        C.update( A[i] , add[i] + x );
                    fix( belong[l] , 0 , root );
                    C.set();
                    x = block_add[ belong[r] ];
                    for( register int i = L[ belong[r] ] ; i <= r ; i++ ) //右边上位点加
                        if( A[i] )
                            add[i]++;
                    for( register int i = L[ belong[r] ] ; i <= R[ belong[r] ] ; i++ ) //右边块内重构插入线段树 
                        if( A[i] )
                            C.update( A[i] , add[i] + x );
                    fix( belong[r] , 0 , root );
                    modify( belong[l] + 1 , belong[r] - 1 , root ); //整块上位点向上移动
                }
                for( int x = belong[l] ; x <= belong[r] ; x++ ) //下位点加 
                {
                    if( belong[l] < x && x < belong[r] )
                        block_add[x]++; //整块上位点向上移动 
                    vector < int > & now = B[x];
                    long long res = inf;
                    for( vector < int > :: iterator i = now.begin() ; i != now.end() ; )
                    {
                        if( l <= * i && * i <= r )
                        {
                            if( temp[ a[ * i ] = fa[ a[ * i ] ] ] )
                            {
                                A[ * i ] = temp[ a[ * i ] ]; //加入上位点列表 
                                add[ * i ] = d[ a[ * i ] ] - block_add[x]; //加入的时候认为最深
                                update_all( root ); //延迟更新 
                                insert( x , A[ * i ] , d[ a[ * i ] ] , 0 , root ); //第x个块中第temp[ a[ * i ] ]个关键点被插入最底端上位点 
                                now.erase( i ); //删去下位点列表 
                                continue;
                            }
                            else
                                update_res( res , dep[ a[ * i ] ] );
                        }
                        i++;
                    }
                    update_res( ans[x] , res );
                }
            }
            else
            {
                long long res = inf;
                {
                    vector < int > & now = B[ belong[l] ];
                    for( int i = 0 ; i < now.size() ; i++ ) //左边零散的下位点 
                        if( l <= now[i] && now[i] <= r )
                            update_res( res , dep[ a[ now[i] ] ] );
                }
                {
                    vector < int > & now = B[ belong[r] ];
                    for( int i = 0 ; i < now.size() ; i++ ) //右边零散的下位点 
                        if( l <= now[i] && now[i] <= r )
                            update_res( res , dep[ a[ now[i] ] ] );
                }
                for( int i = belong[l] + 1 ; i <= belong[r] - 1 ; i++ ) //整块的下位点 
                    update_res( res , ans[i] );
                C.set();
                int x = block_add[ belong[l] ];
                if( belong[l] != belong[r] )
                {
                    update_all( root ); //延迟更新 
                    find( belong[l] + 1 , belong[r] - 1 , 0 , root ); //整块的上位点
                    for( int i = l ; i <= R[ belong[l] ] ; i++ ) //左边零散的上位点 
                        if( A[i] )
                            C.update( A[i] , add[i] + x );
                    x = block_add[ belong[r] ];
                    for( int i = L[ belong[r] ] ; i <= r ; i++ ) //右边零散的上位点 
                        if( A[i] )
                            C.update( A[i] , add[i] + x );
                }
                else
                    for( int i = l ; i <= r ; i++ ) //零散的上位点 
                        if( A[i] )
                            C.update( A[i] , add[i] + x );
                for( int i = 1 ; i <= cnt ; i++ ) //合并两个答案 
                    if( C.a[i] >= 0 )
                        update_res( res , la[i][ C.a[i] ] );
                print( res , 10 );
            }
        }
    } 
    return 0;
}