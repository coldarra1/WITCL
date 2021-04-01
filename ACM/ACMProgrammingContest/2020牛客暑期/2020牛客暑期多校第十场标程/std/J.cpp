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

const int N=507,INF=1e9+7,NPOS=-1;
ll base[N];
struct Matrix
{
	int n;
	ll a[N][N];
};
struct KuhnMunkres:Matrix
{
	ll hl[N],hr[N],slk[N];
	int fl[N],fr[N],vl[N],vr[N],pre[N],q[N],ql,qr;
	int check(int i)
	{
		if(vl[i]=1,fl[i]!=NPOS)return vr[q[qr++]=fl[i]]=1;
		while(i!=NPOS)swap(i,fr[fl[i]=pre[i]]);
		return 0;
	}
	void bfs(int s)
	{
		fill(slk,slk+n,INF),fill(vl,vl+n,0),fill(vr,vr+n,0);
		for(vr[q[ql=0]=s]=qr=1;;)
		{
			for(ll d; ql<qr;)
				for(int i=0,j=q[ql++]; i<n; ++i)
					if(!vl[i]&&slk[i]>=(d=hl[i]+hr[j]-a[i][j])) {
						if(pre[i]=j,d)slk[i]=d;
						else if(!check(i))return;
					}
			ll d=INF;
			for(int i=0; i<n; ++i)
				if(!vl[i]&&d>slk[i])d=slk[i];
			for(int i=0; i<n; ++i)
			{
				if(vl[i])hl[i]+=d;
				else slk[i]-=d;
				if(vr[i])hr[i]-=d;
			}
			for(int i=0; i<n; ++i)
				if(!vl[i]&&!slk[i]&&!check(i))return;
		}
	}
	int ask()
	{
		fill(fl,fl+n,NPOS),fill(fr,fr+n,NPOS),fill(hr,hr+n,0);
		fill(pre,pre+n,0);
		for(int i=0; i<n; ++i)hl[i]=*max_element(a[i],a[i]+n);
		for(int j=0; j<n; ++j)bfs(j);
		int s=0;
		for (int j=0;j<n;j++) s+=a[j][fl[j]];
		return s;
	}
} km;

int n;
struct tree {
	ll hv[N];
	int sz[N];
	VI e[N];
	int rt;
	vector<PII> psize;
	void dfs(int u) {
		sz[u]=1;
		for (auto v:e[u]) {
			dfs(v);
			sz[u]+=sz[v];
		}
		hv[u]=base[sz[u]];
		for (auto v:e[u]) hv[u]=(ll)hv[u]*(base[sz[u]]+hv[v])%mod;
	}
	void init() {
		rep(i,1,n+1) {
			int f;
			scanf("%d",&f);
			if (f==0) rt=i;
			else e[f].pb(i);
		}
		dfs(rt);
		rep(i,1,n+1) psize.pb(mp(sz[i],i));
		sort(all(psize));
	}
}t1,t2;
int dp[N][N];
int main() {
	scanf("%d",&n);
	rep(i,0,n+1) base[i]=rnd(mod);
	t1.init(); t2.init();
	for (auto f1:t1.psize) for (auto f2:t2.psize) if (t1.hv[f1.se]==t2.hv[f2.se]) {
		int u1=f1.se,u2=f2.se;
		map<int,VI> s1,s2;
		set<int> val;
		for (auto v1:t1.e[u1]) s1[t1.hv[v1]].pb(v1),val.insert(t1.hv[v1]);
		for (auto v2:t2.e[u2]) s2[t2.hv[v2]].pb(v2);
		int ans=0;
		for (auto v:val) {
			auto p1=s1[v],p2=s2[v];
			assert(SZ(p1)==SZ(p2));
			km.n=SZ(p1);
			rep(i,0,SZ(p1)) rep(j,0,SZ(p2)) km.a[i][j]=dp[p1[i]][p2[j]];
			ans+=km.ask();
		}
		dp[u1][u2]=ans+(u1==u2);
		//printf("%d %d %d\n",u1,u2,dp[u1][u2]);
	}
	printf("%d\n",n-dp[t1.rt][t2.rt]);
}