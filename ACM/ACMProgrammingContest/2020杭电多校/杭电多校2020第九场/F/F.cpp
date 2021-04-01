#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
mt19937 mrand(random_device{}()); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

VI dst[15][15][15];
vector<VI> od[15][15][15];
int n,board[40];
int bpos[40][40],pbpos[10][40][40];
vector<VI> row[40],col[40],prow[10][40],pcol[10][40];


VI analysis(vector<VI> f,int n) {
	VI s(n,0);
	for (auto p:f) rep(i,0,n) s[i]|=(1<<p[i]);
	return s;
}

bool eliminate(vector<VI> &f,VI t) {
	vector<VI> g;
	for (auto p:f) {
		bool valid=1;
		rep(i,0,n) if (!(t[i]&(1<<p[i]))) valid=0;
		if (valid) g.pb(p);
	}
	bool del=SZ(g)<SZ(f);
	f=g;
	return del;
}


void init() {
	int p[20];
	rep(n,1,8+1) {
		rep(i,1,n+1) p[i]=i;
		while (1) {
			int mx1=0,c1=0;
			int mx2=0,c2=0;
			rep(i,1,n+1) {
				if (p[i]>mx1) mx1=p[i],c1++;
			}
			per(i,1,n+1) {
				if (p[i]>mx2) mx2=p[i],c2++;
			}
			//if (n==6) printf("zz %d %d\n",c1,c2);
			od[n][c1][c2].pb(VI(p+1,p+n+1));
			od[n][c1][0].pb(VI(p+1,p+n+1));
			od[n][0][c2].pb(VI(p+1,p+n+1));
			if (!next_permutation(p+1,p+n+1)) break;
		}
		rep(j,0,n+1) rep(k,0,n+1) dst[n][j][k]=analysis(od[n][j][k],n);
		dst[n][0][0]=VI(n,((1<<(n+1))-2));
	}
}

vector<VI> faster_gen(VI con,int det) {
	int bpos=(1<<n)-1;
	rep(i,0,n) con[i]>>=det;
	vector<VI> ss;
	int seq[20];
	function<void(int)> dfs=[&](int d) {
		if (d==n) {
			ss.pb(VI(seq,seq+n));
			//printf("zz %d\n",bpos);
		} else {
			rep(i,0,n) if ((bpos&con[d])&(1<<i)) {
				bpos^=(1<<i);
				seq[d]=i+det;
				dfs(d+1);
				bpos^=(1<<i);
			}
		}
	};
	dfs(0);
	return ss;
}

int _;
void convert() {
	scanf("%d",&n);
	rep(i,0,4*n) scanf("%d",board+i);
	rep(i,0,n) rep(j,0,n) bpos[i][j]=(1<<(n+1))-2;
	rep(i,0,n) rep(j,0,n) {
		bpos[i][j]&=dst[n][board[i+2*n]][board[i+3*n]][j];
		bpos[j][i]&=dst[n][board[i]][board[i+n]][j];
	}
	rep(i,0,n) {
		if (board[i+2*n]==0&&board[i+3*n]==0) {
			row[i]=faster_gen(VI(bpos[i],bpos[i]+n),1);
		} else row[i]=od[n][board[i+2*n]][board[i+3*n]];
		//printf("zz %d %d %d %d\n",i,board[i+2*n],board[i+3*n],SZ(row[i]));
	}
	rep(i,0,n) {
		if (board[i]==0&&board[i+n]==0) {
			VI clue;
			rep(j,0,n) clue.pb(bpos[j][i]);
			col[i]=faster_gen(clue,1);
		} else col[i]=od[n][board[i]][board[i+n]];
	}
	//rep(i,0,n) rep(j,0,n) printf("%d%c",bpos[i][j]," \n"[j==n-1]);
}


bool eliminate_b() {
	bool suc=0;
	rep(i,0,n) {
		VI clue;
		rep(j,0,n) clue.pb(bpos[i][j]);
		suc|=eliminate(row[i],clue);
	}
	rep(i,0,n) {
		VI clue;
		rep(j,0,n) clue.pb(bpos[j][i]);
		suc|=eliminate(col[i],clue);
	}
	return suc;
}
bool analysis_b() {
	bool suc=0;
	rep(i,0,n) {
		VI p=analysis(row[i],n);
		rep(j,0,n) {
			if ((p[j]&bpos[i][j])!=bpos[i][j]) suc=1;
			bpos[i][j]=bpos[i][j]&p[j];
		}
	}
	rep(i,0,n) {
		VI p=analysis(col[i],n);
		rep(j,0,n) {
			if ((p[j]&bpos[j][i])!=bpos[j][i]) suc=1;
			bpos[j][i]=bpos[j][i]&p[j];
		}
	}
	return suc;
}

bool solve_b() {
	return eliminate_b()&&analysis_b();
}

bool solve_n() {
	bool suc=0;
	rep(i,1,n+1) {
		VI clue(n,0);
		rep(j,0,n) rep(k,0,n) if (bpos[j][k]&(1<<i)) clue[j]|=(1<<k);
		vector<VI> qpos=faster_gen(clue,0);
		auto fc=analysis(qpos,n);
		rep(j,0,n) rep(k,0,n) if ((bpos[j][k]&(1<<i))&&((fc[j]&(1<<k))==0)) {
			suc=1;
			bpos[j][k]^=(1<<i);
		}
	}
	return suc;
}

int finished() {
	rep(i,0,n) rep(j,0,n) if (bpos[i][j]==0) return -1;
	rep(i,0,n) rep(j,0,n) if (__builtin_popcount(bpos[i][j])>1) return 0;
	return 1;
}

bool trialanderr(int step) {
	rep(i,0,n) prow[step][i]=row[i],pcol[step][i]=col[i];
	rep(i,0,n) rep(j,0,n) pbpos[step][i][j]=bpos[i][j];
	vector<VI> vpos;
	rep(i,0,n) rep(j,0,n) if (__builtin_popcount(bpos[i][j])>1) {
		vpos.pb(VI{__builtin_popcount(bpos[i][j]),SZ(row[i])+SZ(col[j]),i,j});
	}
	bool suc=0;
	sort(all(vpos));
	for (auto p:vpos) rep(k,1,n+1) if (pbpos[step][p[2]][p[3]]&(1<<k)) {
		rep(i,0,n) row[i]=prow[step][i],col[i]=pcol[step][i];
		rep(i,0,n) rep(j,0,n) bpos[i][j]=pbpos[step][i][j];
		bpos[p[2]][p[3]]=(1<<k);
		while (solve_b()||solve_n());
		int d=finished();
		if (d==1) return 1;
		if (d==-1) {
			pbpos[step][p[2]][p[3]]^=(1<<k);
			rep(i,0,n) row[i]=prow[step][i],col[i]=pcol[step][i];
			rep(i,0,n) rep(j,0,n) bpos[i][j]=pbpos[step][i][j];
			while (solve_b()||solve_n());
			rep(i,0,n) prow[step][i]=row[i],pcol[step][i]=col[i];
			rep(i,0,n) rep(j,0,n) pbpos[step][i][j]=bpos[i][j];
			suc=1;
			//return 1;
		}
	}
	return suc;
}

void solve() {
	convert();
	while (1) {
		while (solve_b()||solve_n());
		if (finished()==0) {
			if (!trialanderr(1)) break;
		} else break;
	}
	rep(i,0,n) rep(j,0,n) {
		rep(k,1,n+1) if (bpos[i][j]&(1<<k)) printf("%d",k);
		printf("%c"," \n"[j==n-1]);
	}
}

int main() {
	init();
	for (scanf("%d",&_);_;_--) {
		solve();
	}
}
