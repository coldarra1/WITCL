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

int N=100000;

inline ll mul(ll a,ll b,ll p) {
	if (a>=p||a<-p) a%=p; if (a<0) a+=p;
	if (b>=p||b<-p) b%=p; if (b<0) b+=p;
	if (p<=1000000000) return a*b%p;
	else if (p<=1000000000000ll) return (((a*(b>>20)%p)<<20)+(a*(b&((1<<20)-1))))%p;
	else {
		ll d=(ll)floor(a*(long double)b/p+0.5);
		ll ret=(a*b-d*p)%p;
		if (ret<0) ret+=p;
		return ret;
	}
}

ll Inv(ll q,ll m) {
	if (q==0) return 0;
	assert(q>=0);
	ll a1=m,b1=0,a2=q,b2=1,a3,b3,t;
	while (a2!=1) {	t=a1/a2,a3=a1-t*a2,b3=b1-mul(t,b2,m),
		a1=a2,a2=a3,b1=b2,b2=b3;if (b2<0) b2+=m;}
	return b2;
}
ll merge(ll a,ll b,ll c,ll d) { // x=a (mod b) x=c (mod d)
	c-=a;
	ll t=mul(c,Inv(b,d),d);
	if (t<0) t+=d;
	return b*t+a;
}
const int M=101000;
const ll X=1000000000000000000ll;
vector<PII> pr[M];

int q;
vector<pair<ll,int>> que[M];
int ret[1010000];
ll ans[M];
int main() {
	for (int x=1;x*x<=N;x++) for (int y=x;(y-x)*x<=N;y++) if (gcd(x,y)==1) {
		int fa=(y-(ll)x*x%y)%y;
		int fb=(x-(ll)y*y%x)%x;
		ll a=merge(fb,x,fa,y);
		//if ((y-x)*x>a) continue;
		while (a<=N) {
			if ((ll)(x*x+a)/y>x||(x==1&&y==1)) pr[a].pb(mp(x,y));
			a=a+(ll)x*y;
		}
	}
	scanf("%d",&q);
	rep(i,0,q) {
		int a;
		ll n;
		scanf("%d%lld",&a,&n);
		que[a].pb(mp(n,i));
	}
	int mt=0;
	for (int a=1;a<=N;a++) {
		int t=0;
		for (auto p:pr[a]) {
			ll x=p.fi,y=p.se;
			while (1) {
				assert(x<=y);
				ans[t++]=y;
				long double nx=((long double)y*y+a)/x;
				//if (a<=3) printf("%d %lld %lld\n",a,x,y);
				if (nx>2e18) break;
				ll fx=(ll)(nx+0.1);
				if (fx<=X) x=y,y=fx;
				else break;
			}
		}
		mt=max(mt,t);
		//printf("%d %d %d\n",a,t,mt);
		sort(ans,ans+t);
		for (auto q:que[a]) {
			ret[q.se]=upper_bound(ans,ans+t,q.fi)-ans;
		}
	}
	rep(i,0,q) printf("%d\n",ret[i]);
}