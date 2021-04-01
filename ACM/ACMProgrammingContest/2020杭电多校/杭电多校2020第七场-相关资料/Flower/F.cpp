#include<cstdio>
#include<vector>
#include<algorithm>
#define MAX 100005
#define logmax 19
using namespace std;
typedef long long ll;
struct hana
{
	int x,r,w;
}a[MAX];
int T,siz[MAX],mp[MAX],dep[MAX],fr[logmax][MAX];
int n,x,y,m,f[MAX],ff[logmax][MAX],vis[MAX],uh[logmax][MAX];
ll ans=0,sum;
vector<ll>tr[logmax][MAX];
vector<int>s[MAX];
void init()
{
	for(int i=1;i<=n;i++)
	{
		vis[i]=0,ans=0,s[i].clear();
		for(int j=1;j<logmax;j++)tr[j][i].clear();
	}
}
int lowbit(int p){return p&-p;}
ll query(int st,int x,int p)
{
	ll ans=0;
	while(p)
	{
		ans+=tr[st][x][p];
		p-=lowbit(p);
	}
	return ans;
}
bool cmp(hana a,hana b)
{
	int x=dep[a.x]-a.r,y=dep[b.x]-b.r;
	if(x!=y)return x>y;
	if(a.r!=b.r)return a.r<b.r;
	return a.w<b.w;
}
void find_centre(int &rt,int p,int al,int fp)
{
	int v; 
	siz[p]=1;mp[p]=0;
	if(al==n)
	{
		fr[0][p]=fp;
		dep[p]=dep[fp]+1;
	}
	for(int i=0;i<s[p].size();i++)
	{
		v=s[p][i];
		if(v==fp)continue;
		if(vis[v])continue;
		find_centre(rt,v,al,p);
		siz[p]+=siz[v];
		mp[p]=max(mp[p],siz[v]);
	}
	mp[p]=max(mp[p],al-siz[p]);
	if(mp[p]<mp[rt])rt=p;
}
void dfs(int p,int fp,int st)
{
	int i;
	int v;
	siz[p]=1;
	if(vis[p]!=st)ff[st][p]=ff[st][fp]+1;
	for(int i=0;i<s[p].size();i++)
	{
		v=s[p][i];
		if(vis[v])continue;
		if(v==fp)continue;
		if(!ff[st][p])uh[st][v]=v;
		else uh[st][v]=uh[st][p];
		dfs(v,p,st);
		siz[p]+=siz[v];
	}
}
void node_divide(int p,int sz,int pre,int st)
{
	int i,rt=0;
	int v;
	find_centre(rt,p,sz,0);
	f[rt]=pre;
	ff[st][rt]=0;
	uh[st][rt]=rt;
	vis[rt]=st;
	dfs(rt,0,st);
	tr[st][rt].resize(siz[rt]+2);
	for(i=0;i<s[rt].size();i++)
	{
		v=s[rt][i];
		if(vis[v])continue;
		tr[st][v].resize(siz[v]+2);
		node_divide(v,siz[v],rt,st+1);
	}
}
ll ask(int x,int r)
{
	int st=vis[x],y;
	ll sum=0;
	sum=query(st,x,min(r+1,(int)tr[st][x].size()-1));
	st--;y=f[x];
	while(st)
	{
		if(ff[st][x]<=r)
		{
			sum+=query(st,y,min(r+1-ff[st][x],(int)tr[st][y].size()-1));
			sum-=query(st,uh[st][x],min(r+1-ff[st][x],(int)tr[st][uh[st][x]].size()-1));
		}
		st--;y=f[y];
	}
	return sum;
}
void add(int st,int x,int p,ll v)
{
	int cr=(int)tr[st][x].size()-1;
	while(p<=cr)
	{
		tr[st][x][p]+=v;
		p+=lowbit(p);
	}
}
void put_into(int x,ll w)
{
	int st=vis[x],y;
	add(st,x,1,w);
	st--;y=f[x];
	while(st)
	{
		add(st,y,ff[st][x]+1,w);
		add(st,uh[st][x],ff[st][x]+1,w);
		st--;y=f[y];
	}
}
int main()
{
	mp[0]=MAX;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<n;i++)scanf("%d%d",&x,&y),s[x].push_back(y),s[y].push_back(x);
		node_divide(1,n,0,1);
		for(int i=1;i<logmax;i++)for(int j=1;j<=n;j++)fr[i][j]=fr[i-1][fr[i-1][j]];
		for(int i=1;i<=m;i++)scanf("%d%d%d",&a[i].x,&a[i].r,&a[i].w);
		sort(a+1,a+m+1,cmp);
		for(int i=1;i<=m;i++)
		{
			sum=ask(a[i].x,a[i].r);
			if(sum>=a[i].w)continue;
			ans+=a[i].w-sum;
			x=a[i].x;
			for(int j=0;j<logmax;j++)if((1<<j)&a[i].r)x=fr[j][x];
			if(!x)x=1;
			put_into(x,a[i].w-sum);
		}
		printf("%lld\n",ans);
		init();
	}
	return 0;
}
