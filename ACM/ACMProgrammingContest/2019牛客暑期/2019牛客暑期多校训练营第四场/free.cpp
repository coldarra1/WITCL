#include<bits/stdc++.h>
using namespace std;

typedef unsigned int u32;
typedef pair<int,int> pii;
template <typename T> void chmin(T &x,const T &y)
{
	if(x>y)x=y;
}
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
const int N=1000+5;
vector<pii>lk[N];
int n,dp[N],dp0[N];

void upd()
{
	priority_queue<pii>heap;
	rep(i,1,n)heap.push({-dp[i],i});
	while(!heap.empty())
	{
		pii p=heap.top();
		heap.pop();
		int x=p.second;
		if(-p.first!=dp[x])continue;
		for(auto e:lk[x])
		{
			int y=e.first;
			if(dp[y]>dp[x]+e.second)
				heap.push({-(dp[y]=dp[x]+e.second),y});
		}
	}
}

int main()
{
	//freopen("1.in","r",stdin);//freopen("tmp","w",stdout);
	int m,S,T,k;
	cin>>n>>m>>S>>T>>k;
	rep(i,1,m)
	{
		int x,y,l;
		scanf("%d%d%d",&x,&y,&l);
		lk[x].push_back({y,l});
		lk[y].push_back({x,l});
	}
	rep(i,1,n)dp[i]=1e9;
	dp[S]=0;
	upd();
	rep(tmp,1,k)
	{
		rep(i,1,n)dp0[i]=dp[i];
		rep(x,1,n)
		for(auto e:lk[x])chmin(dp[e.first],dp0[x]);
		upd();
	}
	cout<<dp[T];
}
