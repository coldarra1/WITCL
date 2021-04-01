// eddy1021
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
#define eps 1e-9
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
#define N 60
int n , m , a[ N ][ N ] , ta[ N ][ N ] , ans;
void build(){

}
// 1 2
void init(){
  n = getint(); m = getint();
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      a[ i ][ j ] = getint();
}
int sum[ N ][ N ];
int area( int ln , int lm , int rn , int rm ){
  return sum[ rn ][ rm ] - sum[ ln - 1 ][ rm ] 
                         - sum[ rn ][ lm - 1 ]
                         + sum[ ln - 1 ][ lm - 1 ];
}
int dp1[ N ][ N ][ N ][ N ]; // for rd find lu     max
int dp2[ N ][ N ][ N ][ N ]; // for lu find rd     max
int dp3[ N ][ N ][ N ][ N ]; // for lu find in rd  min
int dp4[ N ][ N ][ N ][ N ]; // for rd find lu can over down
int dp5[ N ][ N ][ N ][ N ]; // for lu find rd can only go right
int dp6[ N ]; // within left
int dp7[ N ]; // within right
int dp8[ N ][ N ][ N ][ N ]; // cross up-down
int dp9[ N ][ N ][ N ][ N ]; // cross left-right
bool got[ N ][ N ][ N ][ N ];
void cal(){
  for( int li = 1 ; li <= n ; li ++ )
    for( int lj = 1 ; lj <= m ; lj ++ )
      for( int ri = li ; ri <= n ; ri ++ )
        for( int rj = lj ; rj <= m ; rj ++ ){
          int tans;
// 8
          tans = dp1[ ri ][ rj ][ li ][ lj ] +
                     dp2[ li ][ lj ][ ri ][ rj ] -
                     2 * area( li , lj , ri , rj );
          ans = max( ans , tans );
// @
          tans = dp1[ ri ][ rj ][ li ][ lj ] -
                     dp3[ li ][ lj ][ ri ][ rj ];
          ans = max( ans , tans );
// T
          tans = dp4[ ri ][ rj ][ li ][ lj ] +
                     dp5[ li ][ lj ][ ri ][ rj ] -
                     2 * area( li , lj , ri , rj );
          ans = max( ans , tans );
// x
          tans = dp8[ li ][ lj ][ ri ][ rj ] +
                     dp9[ li ][ lj ][ ri ][ rj ] -
                     2 * area( li , lj , ri , rj );
          ans = max( ans , tans );
        }
  for( int i = 1 ; i <= m ; i ++ )
    dp6[ i ] = max( dp6[ i ] , dp6[ i - 1 ] );
  for( int i = m ; i >= 1 ; i -- )
    dp7[ i ] = max( dp7[ i ] , dp7[ i + 1 ] );
  for( int i = 1 ; i < m ; i ++ )
    ans = max( ans , dp6[ i ] + dp7[ i + 1 ] );
}
void DP( int li , int lj , int ri , int rj ){
  if( got[ li ][ lj ][ ri ][ rj ] ) return;
  got[ li ][ lj ][ ri ][ rj ] = true;
  int tmxud , tmxlr;
  tmxud = tmxlr = area( li , lj , ri , rj );
  if( li > 1 ){
    DP( li - 1 , lj , ri , rj );
    tmxud = max( tmxud , dp8[ li - 1 ][ lj ][ ri ][ rj ] );
  }
  if( ri < n ){
    DP( li , lj , ri + 1 , rj );
    tmxud = max( tmxud , dp8[ li ][ lj ][ ri + 1 ][ rj ] );
  }
  dp8[ li ][ lj ][ ri ][ rj ] = tmxud;
  if( lj > 1 ){
    DP( li , lj - 1 , ri , rj );
    tmxlr = max( tmxlr , dp9[ li ][ lj - 1 ][ ri ][ rj ] );
  }
  if( rj < m ){
    DP( li , lj , ri , rj + 1 );
    tmxlr = max( tmxlr , dp9[ li ][ lj ][ ri ][ rj + 1 ] );
  }
  dp9[ li ][ lj ][ ri ][ rj ] = tmxlr;
}
void pre_cal(){
  for( int i = 0 ; i < N ; i ++ ) dp6[ i ] = dp7[ i ] = 0;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      for( int ii = i ; ii <= n ; ii ++ )
        for( int jj = j ; jj <= m ; jj ++ )
          got[ i ][ j ][ ii ][ jj ] = false;
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      sum[ i ][ j ] = a[ i ][ j ] + sum[ i - 1 ][ j ] 
                                  + sum[ i ][ j - 1 ]
                                  - sum[ i - 1 ][ j - 1 ];
  for( int li = n ; li >= 1 ; li -- )
    for( int lj = 1 ; lj <= m ; lj ++ ){
      for( int ri = n ; ri >= li ; ri -- )
        for( int rj = m ; rj >= lj ; rj -- ){
          int tmx = area( li , lj , ri , rj );
          if( rj < m ) tmx = max( tmx , dp2[ li ][ lj ][ ri ][ rj + 1 ] );
          if( ri < n ) tmx = max( tmx , dp2[ li ][ lj ][ ri + 1 ][ rj ] );
          dp2[ li ][ lj ][ ri ][ rj ] = tmx;
          tmx = area( li , lj , ri , rj );
          if( rj < m ) tmx = max( tmx , dp5[ li ][ lj ][ ri ][ rj + 1 ] );
          dp5[ li ][ lj ][ ri ][ rj ] = tmx;
        }
      for( int ri = li ; ri <= n ; ri ++ )
        for( int rj = lj ; rj <= m ; rj ++ ){
          int tmn = area( li , lj , ri , rj );
          if( ri > li ) tmn = min( tmn , dp3[ li ][ lj ][ ri - 1 ][ rj ] );
          if( rj > lj ) tmn = min( tmn , dp3[ li ][ lj ][ ri ][ rj - 1 ] );
          dp3[ li ][ lj ][ ri ][ rj ] = tmn;
        }
      for( int ri = 1 ; ri <= li ; ri ++ )
        for( int rj = 1 ; rj <= lj ; rj ++ ){
          int tmx = area( ri , rj , li , lj );
          if( ri > 1 ) tmx = max( tmx , dp1[ li ][ lj ][ ri - 1 ][ rj ] );
          if( rj > 1 ) tmx = max( tmx , dp1[ li ][ lj ][ ri ][ rj - 1 ] );
          dp1[ li ][ lj ][ ri ][ rj ] = tmx;
          if( li < n ) tmx = max( tmx , dp4[ li + 1 ][ lj ][ ri ][ rj ] );
          dp4[ li ][ lj ][ ri ][ rj ] = tmx;

          ans = max( ans , area( ri , rj , li , lj ) );
          dp6[ lj ] = max( dp6[ lj ] , area( ri , rj , li , lj ) );
          dp7[ rj ] = max( dp7[ rj ] , area( ri , rj , li , lj ) );
          DP( ri , rj , li , lj );
        }
    }
}
void rotate(){
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      ta[ j ][ n - i + 1 ] = a[ i ][ j ];
  swap( n , m );
  for( int i = 1 ; i <= n ; i ++ )
    for( int j = 1 ; j <= m ; j ++ )
      a[ i ][ j ] = ta[ i ][ j ];
}
void solve(){
  for( int i = 0 ; i < 4 ; i ++ ){
    pre_cal();
    cal();
    rotate();
  }
  cout << ans << endl;
}
int main(){
    build();
//    __ = getint();
    while( __ -- ){
        init();
        solve();
    }
}
