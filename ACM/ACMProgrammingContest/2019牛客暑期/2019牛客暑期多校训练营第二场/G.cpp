// edd_y1021
#include <bits/stdc++.h>
using namespace std;
typedef double D;
typedef long long ll;
typedef pair<int,int> PII;
#define mod9 1000000009ll
#define mod7 1000000007ll
#define INF  1023456789ll
#define INF16 10000000000000000ll
#define FI first
#define SE second
#define PB push_back
#define MP make_pair
#define MT make_tuple
#define eps 1e-7
#define SZ(x) (int)(x).size()
#define ALL(x) (x).begin(), (x).end()
ll getint(){
    ll _x=0,_tmp=1; char _tc=getchar();    
    while( (_tc<'0'||_tc>'9')&&_tc!='-' ) _tc=getchar();
    if( _tc == '-' ) _tc=getchar() , _tmp = -1;
    while(_tc>='0'&&_tc<='9') _x*=10,_x+=(_tc-'0'),_tc=getchar();
    return _x*_tmp;
}
ll mypow( ll _a , ll _x , ll _mod ){
    if( _x == 0 ) return 1ll;
    ll _tmp = mypow( _a , _x / 2 , _mod );
    _tmp = ( _tmp * _tmp ) % _mod;
    if( _x & 1 ) _tmp = ( _tmp * _a ) % _mod;
    return _tmp;
}
bool equal( D _x ,  D _y ){
    return _x > _y - eps && _x < _y + eps;
}
int __ = 1 , cs;
/*********default*********/
#define N 1010
#define X FI
#define Y SE
typedef pair<D,D> PT;
int n , x1[ N ] , _y1[ N ] , x2[ N ] , _y2[ N ];
PT s1[ N ] , s2[ N ];
int pn , res[ N * N ];
vector<PT> pset;
vector< pair<D,int> > a[ N ];
PT operator+( const PT& p1 , const PT& p2 ){
  return MP( p1.X + p2.X , p1.Y + p2.Y );
}
PT operator-( const PT& p1 , const PT& p2 ){
  return MP( p1.X - p2.X , p1.Y - p2.Y );
}
PT operator*( const PT& tp , const D& tk ){
  return MP( tp.X * tk , tp.Y * tk );
}
D operator%( const PT& p1 , const PT& p2 ){
  return ( p1.X * p2.X ) +
         ( p1.Y * p2.Y );
}
D operator^( const PT& p1 , const PT& p2 ){
  return ( p1.X * p2.Y ) -
         ( p1.Y * p2.X );
}
PT inter( PT p1 , PT p2 , PT q1 , PT q2 ){
    D f1 = ( p2 - p1 ) ^ ( q1 - p1 );
  D f2 = ( p2 - p1 ) ^ ( p1 - q2 );
    D f = ( f1 + f2 );
    return q1 * ( f2 / f ) + q2 * ( f1 / f );
}
void build(){

}
vector< pair<int,bool> > v[ N * N ];
vector<D> ans;
bool parel( int idxi , int idxj ){
  return ( _y2[ idxi ] - _y1[ idxi ] ) * ( x2[ idxj ] - x1[ idxj ] ) ==
         ( _y2[ idxj ] - _y1[ idxj ] ) * ( x2[ idxi ] - x1[ idxi ] );
}
void init(){
  n = getint();
  for( int i = 0 ; i < n ; i ++ ){
    x1[ i ] = getint();
    _y1[ i ] = getint();
    x2[ i ] = getint();
    _y2[ i ] = getint();
    s1[ i ] = MP( (D)x1[ i ] , (D)_y1[ i ] );
    s2[ i ] = MP( (D)x2[ i ] , (D)_y2[ i ] );
  }
  pn = 0;
  for( int i = 0 ; i < n ; i ++ )
    for( int j = i + 1 ; j < n ; j ++ ){
      if( parel( i , j ) ) continue;
      PT pi = inter( s1[ i ] , s2[ i ] ,
                     s1[ j ] , s2[ j ] );
      pset.PB( pi );
      a[ i ].PB( MP( ( pi - s1[ i ] ) % ( s2[ i ] - s1[ i ] ) , pn ) );
      a[ j ].PB( MP( ( pi - s1[ j ] ) % ( s2[ j ] - s1[ j ] ) , pn ) );
      pn ++;
    }
  for( int i = 0 ; i < n ; i ++ )
    sort( ALL( a[ i ] ) );
  for( int i = 0 ; i < n ; i ++ )
    for( int j = 1 ; j < (int)a[ i ].size() ; j ++ ){
      v[ a[ i ][ j - 1 ].SE ].PB( MP( a[ i ][ j ].SE , true ) );
      v[ a[ i ][ j ].SE ].PB( MP( a[ i ][ j - 1 ].SE , true ) );
      res[ a[ i ][ j - 1 ].SE ] ++;
      res[ a[ i ][ j ].SE ] ++;
    }
}
void test( int now ){
  int st = now;
  vector<PII> tmp;
  for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
    if( v[ now ][ i ].SE ){
      tmp.PB( MP( now , i ) );
      now = v[ now ][ i ].FI;
      break;
    }
  int pre = st;
  while( now != st ){
    int tmx = -1; D tt = -1;
    for( int i = 0 ; i < (int)v[ now ].size() ; i ++ )
      if( v[ now ][ i ].SE ){
        int nxt = v[ now ][ i ].FI;
        if( nxt == pre ) continue;
        D ttt = ( pset[ now ] - pset[ pre ] ) ^
                ( pset[ nxt ] - pset[ now ] );
        if( tmx == -1 || ( ttt > tt ) )
          tmx = i, tt = ttt;
      }
    if( tmx == -1 || !( tt > 0 ) ){
      for( int i = 0 ; i < (int)tmp.size() ; i ++ ){
        v[ tmp[ i ].FI ][ tmp[ i ].SE ].SE = false;
        res[ tmp[ i ].FI ] --;
      }
      return;
    }
    if( tt > 0 ){
      tmp.PB( MP( now , tmx ) );
      int nxt = v[ now ][ tmx ].FI;
      pre = now;
      now = nxt;
    }
  }
  D area = 0.0;
  for( int i = 0 ; i < (int)tmp.size() ; i ++ ){
    int tnow = tmp[ i ].FI;
    int tnxt = v[ tnow ][ tmp[ i ].SE ].FI;
    area += pset[ tnow ] ^ pset[ tnxt ];
    v[ tnow ][ tmp[ i ].SE ].SE = false;
    res[ tnow ] --;
  }
  area *= 0.5;
  if( area < 0.0 ) area *= -1.0;
  ans.PB( area );
}
void pre_solve(){
  for( int i = 0 ; i < pn ; i ++ )
    while( res[ i ] )
      test( i );
}
void solve(){
  pre_solve();
  sort( ALL( ans ) );
  int _sz = (int)ans.size();
  printf( "%d %.6f %.6f\n" , _sz , ans[ _sz - 1 ] , ans[ 0 ] );
  int qq = getint(); while( qq -- ){
    int qe = getint();
    if( qe > _sz || qe < 1 ) puts( "Invalid question" );
    else printf( "%.6f\n" , ans[ _sz - qe ] );
  }
}
int main(){
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
