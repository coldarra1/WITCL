#include <bits/stdc++.h>

using namespace std;
typedef vector<string> vecstr;
typedef pair<vecstr, vecstr> pr;
typedef pair<int,int> pii;
const int N = 4010;
const int BASE = 131;
const int M1 = 998244353;
const int M2 = 1e9+7;
const char *branch1 = "<<<<<<< branch1";
const char *sepa = "=======";
const char *branch2 = ">>>>>>> branch2";
int _w;

int raw_n;
string raw_str[N];

void input() {
	raw_n = 0;
	string tmp;
	while(1) {
		getline(cin, tmp);
		if( tmp.size() && tmp.back() == '\r' )
			tmp.pop_back();
		++raw_n;
		raw_str[raw_n] = tmp;
		if( cin.peek() == EOF ) break;
	}
}

pii hsh( const string &str ) {
	int h1 = 0, h2 = 0;
	for( char ch : str ) {
		h1 = int((1LL * h1 * BASE + ch) % M1);
		h2 = int((1LL * h2 * BASE + ch) % M2);
	}
	return pii(h1, h2);
}

vecstr c1, c2;
vector<pii> h1, h2;
int n1, n2;

pr parse( int &now ) {
	if( raw_str[now] == branch1 ) {
		vecstr b1, b2;
		++now;
		while( raw_str[now] != sepa ) {
			assert( now <= raw_n );
			b1.push_back( raw_str[now++] );
		}
		++now;
		while( raw_str[now] != branch2 ) {
			assert( now <= raw_n );
			// printf( "raw_str = %s\n", raw_str[now].c_str() );
			// printf( "sz = %d, cmp = %d\n", (int)raw_str[now].size(), int(raw_str[now] == branch2) );
			// for( char ch : raw_str[now] )
			// printf( "%d ", int(ch) );
			// puts("");
			// for( int i = 0; i < (int)strlen(branch2); ++i )
			// printf( "%d ", int(branch2[i]) );
			// puts("");
			b2.push_back( raw_str[now++] );
		}
		++now;
		return pr(b1, b2);
	} else {
		vecstr rtn;
		while( now <= raw_n && raw_str[now] != branch1 ) {
			// printf( "str = %s\n", raw_str[now].c_str() );
			// printf( "cmp = %d\n", int(raw_str[now] == branch1) );
			rtn.push_back( raw_str[now++] );
		}
		return pr(rtn, rtn);
	}
}

void init() {
	int now = 1;
	while( now <= raw_n ) {
		pr tmp = parse(now);
		for( string str : tmp.first )
			c1.push_back(str);
		for( string str : tmp.second )
			c2.push_back(str);
		// printf( "now = %d\n", now );
	}
	n1 = (int)c1.size();
	n2 = (int)c2.size();
	for( string str : c1 )
		h1.push_back( hsh(str) );
	for( string str : c2 )
		h2.push_back( hsh(str) );
}

const short INF = 0x3f3f;
short f[N][N][4];
char trans[N][N][4];

void go( short now, int i, int j, int k, char tr ) {
	if( now < f[i][j][k] ) {
		f[i][j][k] = now;
		trans[i][j][k] = tr;
	}
}

void dp() {
	memset(f, 0x3f, sizeof f);
	f[0][0][0] = 0;
	f[0][0][1] = 2;
	f[0][0][2] = 2;
	f[0][0][3] = 3;
	for( int i = 0; i <= n1; ++i )
		for( int j = 0; j <= n2; ++j ) {
			if( f[i][j][0] != INF ) {
				if( i != n1 && j != n2 && h1[i] == h2[j] ) {
					short now = f[i][j][0] + 1;
					go(now + 0, i+1, j+1, 0, 0);
					go(now + 2, i+1, j+1, 1, 0);
					go(now + 2, i+1, j+1, 2, 0);
					go(now + 3, i+1, j+1, 3, 0);
				}
			}
			if( f[i][j][1] != INF ) {
				if( i != n1 ) {
					short now = f[i][j][1] + 1;
					go(now + 0, i+1, j, 0, -1);
					go(now + 0, i+1, j, 1, -1);
					go(now + 2, i+1, j, 2, -1);
					go(now + 3, i+1, j, 3, -1);
				}
			}
			if( f[i][j][2] != INF ) {
				if( j != n2 ) {
					short now = f[i][j][2] + 1;
					go(now + 0, i, j+1, 0, 2);
					go(now + 2, i, j+1, 1, 2);
					go(now + 0, i, j+1, 2, 2);
					go(now + 3, i, j+1, 3, 2);
				}
			}
			if( f[i][j][3] != INF ) {
				if( i != n1 ) {
					short now = f[i][j][3] + 1;
					go(now + 0, i+1, j, 0, -3);
					go(now + 2, i+1, j, 1, -3);
					go(now + 2, i+1, j, 2, -3);
					go(now + 0, i+1, j, 3, -3);
				}
				if( j != n2 ) {
					short now = f[i][j][3] + 1;
					go(now + 0, i, j+1, 0, 3);
					go(now + 2, i, j+1, 1, 3);
					go(now + 2, i, j+1, 2, 3);
					go(now + 0, i, j+1, 3, 3);
				}
			}
		}
}

vector<string> ans;
queue<string> stk1, stk2;

void calc_trans( int i, int j, int k, int &ni, int &nj, int &nk ) {
	int tr = trans[i][j][k];
	if( tr == 0 ) {
		ni = i-1;
		nj = j-1;
		nk = 0;
	} else {
		ni = i;
		nj = j;
		nk = abs(tr);
		if( tr < 0 ) --ni;
		else --nj;
	}
}

void pop_stack() {
	if( stk1.empty() && stk2.empty() ) {
		;
	} else if( stk1.empty() ) {
		ans.push_back("#endif");
		while( !stk2.empty() ) {
			ans.push_back( stk2.front() );
			stk2.pop();
		}
		ans.push_back("#ifdef branch2");
	} else if( stk2.empty() ) {
		ans.push_back("#endif");
		while( !stk1.empty() ) {
			ans.push_back( stk1.front() );
			stk1.pop();
		}
		ans.push_back("#ifdef branch1");
	} else {
		ans.push_back("#endif");
		while( !stk2.empty() ) {
			ans.push_back( stk2.front() );
			stk2.pop();
		}
		ans.push_back("#else");
		while( !stk1.empty() ) {
			ans.push_back( stk1.front() );
			stk1.pop();
		}
		ans.push_back("#ifdef branch1");
	}
}

void output() {
	int i = n1, j = n2, k = 0;
	while( i != 0 || j != 0 ) {
		int ni, nj, nk;
		calc_trans(i, j, k, ni, nj, nk);
		if( k != nk ) pop_stack();
		if( i != ni && j != nj ) {
			ans.push_back( c1[ni] );
		} else if( i != ni ) {
			stk1.push( c1[ni] );
		} else if( j != nj ) {
			stk2.push( c2[nj] );
		} else {
			assert(0);
		}
		i = ni, j = nj, k = nk;
	}
	pop_stack();
	assert( (int)ans.size() == f[n1][n2][0] );
	reverse(ans.begin(), ans.end());
	for( string str : ans )
		printf( "%s\n", str.c_str() );
}

int main() {
	input();
	init();
	dp();
	output();
	return 0;
}
