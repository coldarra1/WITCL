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

const int N=101000;
int n,q,u,v,w,wt[N],p;
PII e[N];
ll sm[N],ret[N],ans;
multiset<int> s[N];
void gao(int u,int w1,int w2) {
	sm[u]-=w1; sm[u]+=w2;
	ans-=ret[u];
	s[u].erase(s[u].lower_bound(w1));
	s[u].insert(w2);
	int mx=*(--s[u].end());
	ret[u]=max(0ll,2*mx-sm[u]);
	if (sm[u]%2==1&&ret[u]%2==0) ret[u]++;
	ans+=ret[u];
}

int main() {
	scanf("%d%d",&n,&q);
	rep(i,1,n) {
		scanf("%d%d%d",&u,&v,&w);
		s[u].insert(w);
		s[v].insert(w);
		sm[u]+=w;
		sm[v]+=w;
		e[i]=mp(u,v);
		wt[i]=w;
	}
	rep(i,1,n+1) {
		int mx=*(--s[i].end());
		ret[i]=max(0ll,2*mx-sm[i]);
		if (sm[i]%2==1&&ret[i]%2==0) ret[i]++;
		ans+=ret[i];
	}
	printf("%lld\n",ans/2);
	rep(i,0,q) {
		scanf("%d%d",&p,&w);
		int u=e[p].fi,v=e[p].se;
		gao(u,wt[p],w);
		gao(v,wt[p],w);
		wt[p]=w;
		printf("%lld\n",ans/2);
	}
}
