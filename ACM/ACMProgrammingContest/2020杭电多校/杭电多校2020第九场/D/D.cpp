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
// head

typedef int i32;
typedef unsigned int u32;
typedef long long i64;
typedef unsigned long long u64;
typedef __int128_t i128;
typedef __uint128_t u128;

struct Mod64 {
	Mod64():n_(0) {}
	Mod64(u64 n):n_(init(n)) {}
	static u64 init(u64 w) { return reduce(u128(w) * r2); }
	static void set_mod(u64 m) {
		mod=m; assert(mod&1);
		inv=m; rep(i,0,5) inv*=2-inv*m;
		r2=-u128(m)%m;
	}
	static u64 reduce(u128 x) {
		u64 y=u64(x>>64)-u64((u128(u64(x)*inv)*mod)>>64);
		return ll(y)<0?y+mod:y;
	}
	Mod64& operator += (Mod64 rhs) { n_+=rhs.n_-mod; if (ll(n_)<0) n_+=mod; return *this; }
	Mod64 operator + (Mod64 rhs) const { return Mod64(*this)+=rhs; }
	Mod64& operator -= (Mod64 rhs) { n_-=rhs.n_; if (ll(n_)<0) n_+=mod; return *this; }
	Mod64 operator - (Mod64 rhs) const { return Mod64(*this)-=rhs; }
	Mod64& operator *= (Mod64 rhs) { n_=reduce(u128(n_)*rhs.n_); return *this; }
	Mod64 operator * (Mod64 rhs) const { return Mod64(*this)*=rhs; }
	u64 get() const { return reduce(n_); }
	static u64 mod,inv,r2;
	u64 n_;
};
u64 Mod64::mod,Mod64::inv,Mod64::r2;

ll powmodd(ll a,ll b) {
	Mod64 res(1);
	Mod64 c(a);
	for(;b;b>>=1) {if(b&1) res=res*c; c=c*c; }
	return res.get();
}


bool pr[101000];
VI prime;
ll P;
int d[1010],d2[1010],t,tt;
ll inv[10100];
int trytofact(ll x) {
	int s=0;
	for (auto p:prime) {
		while (x%p==0) x/=p,s+=p,d[t++]=p;
		if (p>40&&x>1e15) break;
		if (p>120&&x>1e13) break;
	}
	//printf("oo %lld\n",x);
	if (x==1) return s;
	else return -1;
}

vector<ll> dp[110];
int main() {
	scanf("%lld",&P);
	Mod64::set_mod(P);
	for (int i=2;i<=1000;i++) if (!pr[i]) {
		prime.pb(i);
		for (int j=i*i;j<=1000;j+=i) pr[j]=1;
	}
	for (int i=0;i<SZ(prime);i++) {
		inv[prime[i]]=powmodd(prime[i],P-2);
	}
	dp[0]={1};
	vector<pair<ll,int> > cand;
	for (int s=2;s<=100;s++) {
		for (auto x:prime) {
			if (x>s) break;
			Mod64 rev=Mod64(inv[x]);
			for (auto y:dp[s-x]) dp[s].pb((Mod64(y)*rev).get());
		}
		sort(all(dp[s])); dp[s].erase(unique(all(dp[s])),dp[s].end());
		for (auto x:dp[s]) {
			cand.pb(mp(x,s));
		}
	}
	random_shuffle(all(cand));
	//printf("%d\n",SZ(cand));
	int _;
	for (scanf("%d",&_);_;_--) {
		ll x;
		scanf("%lld",&x);
		int ps=0; Mod64 y(x); ll yy=x;
		int cc=0;
		pair<ll,int> r;
		while (1) {
			if (ps>400) {
				r=cand[rnd(SZ(cand))];
				yy=(y*Mod64(r.fi)).get();
				ps=r.se; tt=0;
			}
			int u=prime[rnd(20)];
			yy=(Mod64(yy)*Mod64(inv[u])).get();
			ps+=u; d2[tt++]=u;
			t=0;
			int o=trytofact(yy);
			if (o!=-1) {
				if (ps+o<=2500) {
					trytofact(powmodd(r.fi,P-2));
					break;
				}
			}
		}
		printf("%d ",t+tt);
		rep(i,0,tt) printf("%d ",d2[i]);
		rep(i,0,t) printf("%d ",d[i]);
		puts("");
	}
	//printf("%d\n",clock());
}