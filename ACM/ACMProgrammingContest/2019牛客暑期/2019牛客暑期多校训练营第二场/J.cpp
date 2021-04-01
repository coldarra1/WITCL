#include <bits/stdc++.h>
using namespace std;
#define M 2048576
#define TM 30485777
#define BS 20000020
const int INT = 999999999;
int n , ptr;
vector< pair< pair<int,int> , int > > vv;
inline int value( int x ){
  while( ptr < n && vv[ ptr ].first.second < x ) ptr ++;
  return vv[ ptr ].second;
}
void init(){
  scanf( "%d" , &n );
  int pre = 0;
  for( int i = 0 ; i < n ; i ++ ){
    int li , ri; scanf( "%d%d" , &li , &ri );
    if( pre < li ) vv.push_back( { { pre , li - 1 } , -1 } );
    vv.push_back( { { li , ri } , +1 } );
    pre = ri + 1;
  }
  if( pre <= INT ) vv.push_back( { { pre , INT } , -1 } );
}
int ps[ M ] , ss[ M ] , pm[ M ] ,  sm[ M ];
void pre_build(){
  n = (int)vv.size();
  for( int i = 0 ; i < n ; i ++ ){
    ss[ i ] = ps[ i ] = ( vv[ i ].first.second - vv[ i ].first.first + 1 ) *
                        vv[ i ].second;
    if( i ) ps[ i ] += ps[ i - 1 ];
  }
  for( int i = n - 2 ; i >= 0 ; i -- )
    ss[ i ] += ss[ i + 1 ];
  for( int i = 0 ; i < n ; i ++ ){
    pm[ i ] = ss[ i ];
    if( i ) pm[ i ] = max( pm[ i ] , pm[ i - 1 ] );
  }
  for( int i = n - 1 ; i >= 0 ; i -- ){
    sm[ i ] = ps[ i ];
    if( i < n - 1 ) sm[ i ] = max( sm[ i ] , sm[ i + 1 ] );
  }
}
vector< pair<int,int> > itv;
void find_useful(){
  for( int i = 0 ; i < n ; i ++ ){
    if( vv[ i ].second > 0 ){
      itv.push_back( vv[ i ].first );
      continue;
    }else{
      int lft = vv[ i ].first.first;
      int rgt = vv[ i ].first.second;
      int lb = pm[ i ] - ss[ i ];
      int rb = sm[ i ] - ps[ i ];
      if( lb + rb >= rgt - lft + 1 ){
        itv.push_back( vv[ i ].first );
        continue;
      }
      if( lb > 0 )
        itv.push_back( { lft , lft + lb - 1 } );
      if( rb > 0 )
        itv.push_back( { rgt - rb + 1 , rgt } );
    }
  }
  size_t sz = 1;
  for( size_t i = 1 ; i < itv.size() ; i ++ )
    if( itv[ i ].first > itv[ sz - 1 ].second + 1 )
      itv[ sz ++ ] = itv[ i ];
    else
      itv[ sz - 1 ].second = itv[ i ].second;
  itv.resize( sz );
}
int cnt[ TM ] , pos , cur;
inline void add( int xi ){
  if( xi <= pos ) cur ++;
  cnt[ xi ] ++;
}
inline void sub( int xi ){
  if( xi <= pos ) cur --;
  cnt[ xi ] --;
}
inline int query( int xi ){
  while( pos < xi ){
    pos ++;
    cur += cnt[ pos ];
  }
  while( pos > xi ){
    cur -= cnt[ pos ];
    pos --;
  }
  return cur;
}
int sv[ TM ];
long long ans;
void find_ans(){
  for( auto _ : itv ){
    int lft = _.first , rgt = _.second;
    int psum = BS; pos = BS; cur = 0;
    add( BS );
    for( int i = lft ; i <= rgt ; i ++ ){
      psum += value( i );
      ans += query( psum - 1 );
      add( sv[ i - lft ] = psum );
    }
    for( int i = lft ; i <= rgt ; i ++ )
      sub( sv[ i - lft ] );
    sub( BS );
  }
}
void solve(){
  pre_build();
  find_useful();
  find_ans();
  cout << ans << endl;
}
int main(){
  init();
  solve();
}
