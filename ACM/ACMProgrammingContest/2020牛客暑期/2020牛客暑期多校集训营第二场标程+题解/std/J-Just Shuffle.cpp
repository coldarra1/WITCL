#include <stdio.h>
#include <algorithm>

using namespace std;

int n , k;
int p[120000];
int vis[120000];
int now[120000] , len;
int pw[120000];
int ans[120000];
int x , y;
void exgcd ( int a , int b ) {
	if ( b == 0 ) {
		x = 1; y = 0;
		return ;
	}
	exgcd ( b , a % b );
	int xx , yy;
	xx = y;
	yy = x - (a/b) * y;
	x = xx; y = yy;
}
int getinv ( int a , int b ) {
	exgcd ( b , a );
	y %= b;
	if ( y < 0 ) y += b;
	return y;
}
void findcycle ( int x ) {
	len = 0;
	do {
		vis[x] = 1;
		now[++len] = x;
		x = p[x];
	} while ( !vis[x] );
}
void work () {
	int i , j , tim , tar;
	scanf ( "%d%d" , &n , &k );
	for ( i = 1 ; i <= n ; i++ ) {
		scanf ( "%d" , &p[i] );
	}
	for ( i = 1 ; i <= n ; i++ ) {
		if ( !vis[i] ) {
			findcycle ( i );
			tim = getinv ( k % len , len );
			//printf ( "%d %d\n" , len , tim );
			//for ( j = 1 ; j <= len ; j++ ) {
			//	printf ( "%d\n" , now[j] );
			//}
			for ( j = 1 , tar = 1 ; j <= len ; j++ ) {
				pw[j] = now[tar];
				tar = (tar+tim-1) % len + 1;
			}
			pw[len+1] = pw[1];
			for ( j = 1 ; j <= len ; j++ ) {
				ans[pw[j]] = pw[j+1];
			}
		}
	}
	for ( i = 1 ; i <= n ; i++ ) {
		printf ( "%d%c" , ans[i] , i==n?'\n':' ' );
	}
}
int main () {
	work ();
	return 0;
}