#include <bits/stdc++.h>
using namespace std;
#define mem(a,b) memset((a),(b),sizeof(a))
#define MP make_pair
#define pb push_back
#define fi first
#define se second
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define sqr(x) (x)*(x)
using namespace __gnu_cxx;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;
typedef pair<int,ll> PIL;
typedef pair<ll,int> PLI;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef vector<PII > VPII;
/************* define end  *************/
void go();
int main(){
	#ifdef tokitsukaze
//		freopen("TEST.txt","r",stdin);
	#endif
	go();return 0;
}
const int INF=0x3f3f3f3f;
const ll LLINF=0x3f3f3f3f3f3f3f3fLL;
const double PI=acos(-1.0);
const double eps=1e-6;
const int MAX=1e5+10;
const ll mod=998244353;
/*********************************  head  *********************************/
struct Fenwick_Tree
{
	#define type int
	type bit[MAX];
	int n;
	void init(int _n)
	{
		n=_n+1;
		for(int i=0;i<=n;i++) bit[i]=0;
	}
	int lowbit(int x){return x&(-x);}
	void insert(int x,type v)
	{
		if(x>n) return;
		while(x<=n)
		{
			bit[x]+=v;
			x+=lowbit(x);
		}
	}
	type get(int x)
	{
		type res=0;
		while(x)
		{
			
			res+=bit[x];
			x-=lowbit(x);
		}
		return res;
	}
	type ask(int l,int r)
	{
		if(l-1<=0) return get(r);
		return get(r)-get(l-1);
	}
	#undef type
}add[2],sub[2];
int v[MAX],col[MAX];
VI mp[MAX];
int l[MAX],r[MAX],tot;
void dfs(int x,int pre)
{
	l[x]=++tot;
	for(auto to:mp[x])
	{
		if(to==pre) continue;
		dfs(to,x);
	}
	r[x]=tot;
}
ll ans[MAX];
struct qry
{
	int id,x,v,sg;
};
vector<qry> qst[MAX];
void go()
{
	int T,n,i,a,b,q,op,x,y,s,f,c;
	ll bt;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			mp[i].clear();
			qst[i].clear();
		}
		for(i=1;i<=n;i++) scanf("%d",&col[i]);
		for(i=1;i<=n;i++)
		{
			scanf("%d",&v[i]);
			qst[col[i]].pb({0,i,v[i],1});
		}
		for(i=1;i<n;i++)
		{
			scanf("%d%d",&a,&b);
			mp[a].pb(b);
			mp[b].pb(a);
		}
		tot=0;
		l[0]=r[0]=0;
		dfs(1,0);
		scanf("%d",&q);
		for(i=1;i<=q;i++)
		{
			scanf("%d%d%d",&op,&x,&y);
			if(op==1)
			{
				qst[col[x]].pb({i,x,v[x],-1});
				v[x]=y;
				qst[col[x]].pb({i,x,v[x],1});
			}
			else
			{
				qst[col[x]].pb({i,x,v[x],-1});
				col[x]=y;
				qst[col[x]].pb({i,x,v[x],1});
			}
			ans[i]=0;
		}
		ans[0]=0;
		for(i=0;i<2;i++)
		{
			add[i].init(n);
			sub[i].init(n);
		}
		for(c=1;c<=n;c++)
		{
			for(s=0;s<20;s++)
			{
				bt=(1LL<<s);
				for(auto it:qst[c])
				{
					f=(it.v>>s)&1;
					ans[it.id]+=it.sg*bt*(add[f^1].ask(1,n)-
					add[f^1].ask(l[it.x],r[it.x])-
					(add[f^1].ask(1,l[it.x])+sub[f^1].ask(1,l[it.x]))
					);
					add[f].insert(l[it.x],it.sg);
					sub[f].insert(r[it.x]+1,-it.sg);
				}
				for(auto it:qst[c])
				{
					f=(it.v>>s)&1;
					add[f].insert(l[it.x],-it.sg);
					sub[f].insert(r[it.x]+1,it.sg);
				}
			}
		}
		for(i=1;i<=q;i++) ans[i]+=ans[i-1];
		for(i=0;i<=q;i++) printf("%lld\n",ans[i]);
	}
} 
