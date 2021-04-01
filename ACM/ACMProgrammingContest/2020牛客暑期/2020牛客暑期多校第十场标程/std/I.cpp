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
mt19937_64 mrand(random_device{}()); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

int _,n;
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d",&n);
		VI x,y;
		rep(i,1,(n+1)/2+1) x.pb(i);
		rep(i,(n+1)/2+1,n+1) y.pb(i);
		vector<PII> p1;
		rep(i,0,SZ(x)) rep(j,0,i) p1.pb(mp(x[i],x[j]));
		rep(i,0,SZ(y)) rep(j,i+1,SZ(x)) p1.pb(mp(y[i],x[j]));
		per(i,0,SZ(x)) rep(j,i,SZ(y)) p1.pb(mp(x[i],y[j]));
		per(i,0,SZ(y)) rep(j,0,i) p1.pb(mp(y[j],y[i]));
		for (auto x:p1) printf("%d %d\n",x.fi,x.se);
		int ts=0;
		rep(i,1,n+1) {
			int s=n*(n-1)/2;
			rep(j,0,SZ(p1)) if (p1[j].fi!=i&&p1[j].se!=i) {
				s--;
			} else break;
			per(j,0,SZ(p1)) if (p1[j].fi!=i&&p1[j].se!=i) {
				s--;
			} else break;
			ts+=s;
		}
		fprintf(stderr,"%d\n",ts);
	}
}