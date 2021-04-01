#include<bits/stdc++.h>
using namespace std;

typedef long long s64;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
const int M=13,T=8000,N=2000+5,D=1e9+7;
namespace HASH
{	
const int D=1e9+7;
s64 w1[M],w2[M];
int ra_32()
{
	return RAND_MAX<=32768?rand():rand()*32768+rand();
}
void init(int m)
{
	rep(i,1,m){w1[i]=ra_32();w2[i]=ra_32();}
}
int *lk,n;
int h[M],q[M];
void dfs(int x)
{
	rep(y,x+1,n)
	if((lk[x]>>y)&1)
		dfs(y);
	int t=0;
	rep(y,x+1,n)
	if((lk[x]>>y)&1)q[++t]=h[y];
	sort(q+1,q+t+1);
	h[x]=0;
	rep(i,1,t)h[x]^=(q[i]*w1[i]+w2[i])%D;
}
int get(int *_lk,int _n)
{
	lk=_lk;n=_n;
	dfs(1);
	return h[1];
}
};
struct Tree
{
	int lk[M],n,v;
	void get_v()
	{
		v=HASH::get(lk,n);
	}
};
int m,tot,be[M],en[M];Tree tree[T];
map<int,int>dy;
void check()
{
	tree[tot+1].get_v();
	if(!dy.count(tree[tot+1].v))
	{
		++tot;
		dy[tree[tot].v]=tot;
	}
}
int *trans[T];

namespace A
{
vector<int>lk[N];
s64 ans,dp[N][T];
int sz[N];
void dfs(int x,int fr)
{
	sz[x]=1;
	dp[x][1]=1;
	for(auto y:lk[x])
	if(y!=fr)
	{
		dfs(y,x);
		per(i,min(m,sz[x]),1)
		per(hi,en[i],be[i])
		{
			s64 v=dp[x][hi];
			if(!v)continue;
			rep(j,1,min(m-i,sz[y]))
			rep(hj,be[j],en[j])(dp[x][trans[hi][hj]]+=v*dp[y][hj])%=D;
		}
		sz[x]+=sz[y];
	}
	rep(i,1,tot)(dp[0][i]+=dp[x][i])%=D;
}
void init()
{
	int n;
	cin>>n;
	rep(i,1,n-1)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		lk[x].push_back(y);
		lk[y].push_back(x);
	}
	dfs(1,0);
}
};
namespace B
{
vector<int>lk[M];
int dfn[M],tot;
void dfs(int x,int fr)
{
	dfn[x]=++tot;
	for(auto y:lk[x])
	if(y!=fr)dfs(y,x);
}
void work()
{
	int m;
	scanf("%d",&m);
	rep(i,1,m)lk[i].clear();
	rep(i,1,m-1)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		lk[x].push_back(y);
		lk[y].push_back(x);
	}
	vector<int>q;
	rep(x,1,m)
	{
		tot=0;
		dfs(x,0);
		Tree nt={};
		nt.n=m;
		rep(i,1,m)
		for(auto j:lk[i])
		if(dfn[i]<dfn[j])nt.lk[dfn[i]]|=1<<dfn[j];
		nt.get_v();
		assert(dy.count(nt.v));
		int now=dy[nt.v];
		bool ap=0;
		for(auto x:q)
		if(x==now){ap=1;break;}
		if(!ap)q.push_back(now);
	}
	s64 ans=0;
	for(auto i:q)(ans+=A::dp[0][i])%=D;
	printf("%d\n",int((ans%D+D)%D));
}
};
void init(int _m)
{
	m=_m;
	HASH::init(m);
	tree[1].n=1;
	be[1]=en[1]=1;
	check();
	rep(sz,2,m)
	{
		be[sz]=tot+1;
		rep(i,be[sz-1],en[sz-1])
		rep(j,1,sz-1)
		{
			tree[tot+1]=tree[i];
			++tree[tot+1].n;
			tree[tot+1].lk[j]|=1<<sz;
			check();
		}
		en[sz]=tot; 
//		cerr<<tot<<endl;
	}
/*	rep(i,1,tot)
	rep(j,i+1,tot)
	if(tree[i].v==tree[j].v)cerr<<i<<" "<<j<<endl;*/
/*	int s=0;
	rep(i,1,m)
	rep(j,1,m-i)s+=(en[i]-be[i]+1)*(en[j]-be[j]+1);
	cerr<<s<<endl;*/
	rep(i,1,m)
	rep(hi,be[i],en[i])trans[hi]=new int [en[m-i]+1];
	rep(i,1,m)
	rep(j,1,m-i)
	rep(hi,be[i],en[i])
	rep(hj,be[j],en[j])
	{
		Tree nt=tree[hi];
		nt.n+=j;
		nt.lk[1]|=1<<i+1;
		rep(x,1,j)nt.lk[i+x]=tree[hj].lk[x]<<i;
		nt.get_v();
		assert(dy.count(nt.v));
		trans[hi][hj]=dy[nt.v];
	}
}

int main()
{
	init(12);
	A::init();
	int tt;
	cin>>tt;
	while(tt--)B::work();
}
