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
mt19937_64 mrand(1); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}

int n,m,s,bk,t,T,K;
const int V=100007;

int dp[2][V],ans;
int state[2][V];
int F(int k,int x) { return ((k)<<(2*(x))); }
int G(int k,int x) { return (((k)>>(2*(x)))&3); }

struct Hash_table {
	int fst[V],nxt[V];
	int mark[V];
	int mt=0;

	void init() {
		//memset(fst,-1,sizeof(fst));
		mt++;
		T=0;
	}
	void insert(int s,int w) {
		int S=s%V;
		if (mark[S]!=mt) fst[S]=-1,mark[S]=mt;
		assert(s>=0);
		//printf("zz %d %d\n",s,w);
		for (int j=fst[S];j!=-1;j=nxt[j]) if (state[K][j]==s) {
			dp[K][j]=max(dp[K][j],w);
			return;
		}
		nxt[T]=fst[S]; fst[S]=T;
		state[K][T]=s;
		dp[K][T]=w;
		T++;
	}
}Hash;
int _,a[20][20];
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d",&n);
		m=n;
		rep(i,1,n+1) rep(j,1,m+1) scanf("%d",&a[i][j]);
		state[0][(t=1)-1]=0;dp[0][0]=0;K=0;
		ans=0;
		rep(i,1,n+1) {
			rep(j,1,m+1) {
				K=1-K;
				Hash.init();
				memset(state[K],0,sizeof(state[K]));
				memset(dp[K],0,sizeof(dp[K]));
				rep(k,0,t) {
					int s=state[1-K][k];
					int val=dp[1-K][k];
					int k1=G(s,j-1),k2=G(s,j);
					if (k1==0&&k2==0) {
						Hash.insert(s^F(3,j-1)^F(3,j),val+a[i][j]);
					}
					if ((k1==0||k1==3)&&(k2==0||k2==3)) {
						if (i+1<=n&&j+1<=m) Hash.insert(s^F(1^k1,j-1)^F(2^k2,j),val);
					} else if (k1==0||k1==3) {
						if (j+1<=m) Hash.insert(s^F(k1,j-1),val);
						if (i+1<=n) Hash.insert(s^F(k1,j-1)^F(k2,j-1)^F(k2,j),val);
					} else if (k2==0||k2==3) {
						if (i+1<=n) Hash.insert(s^F(k2,j),val);
						if (j+1<=m) Hash.insert(s^F(k2,j)^F(k1,j-1)^F(k1,j),val);
					} else if (k1==1 && k2==1) {
						bk=1;
						for (int l=j+1;l<=m;l++) {
							if (G(s,l)==1) bk++; else if (G(s,l)==2) bk--;
							if (bk==0) {
								Hash.insert(s^F(1,j-1)^F(1,j)^F(3,l),val);
								break;
							}
						}
					} else if (k1==2 && k2==2) {
						bk=1;
						for (int l=j-2;l>=1;l--) {
							if (G(s,l)==1) bk--; else if (G(s,l)==2) bk++;
							if (bk==0) {
								Hash.insert(s^F(2,j-1)^F(2,j)^F(3,l),val);
								break;
							}
						}
					} else if (k1==2 && k2==1) Hash.insert(s^F(2,j-1)^F(1,j),val);
					else {
						if (i==n && j==m) ans=max(ans,val);
						if (i==n&&j==m-1&&G(s,m)==0) ans=max(ans,val+a[n][m]);
					}
				}
				t=T;
			}
			rep(k,0,t) {
				state[K][k]<<=2; state[K][k]&=(F(1,m+1)-1);
			}
		}
		printf("%d\n",ans);
	}
}
