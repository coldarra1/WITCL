#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair <ll,ll> pii;
#define rep(i,x,y) for(int i=x;i<y;i++)
#define rept(i,x,y) for(int i=x;i<=y;i++)
#define per(i,x,y) for(int i=x;i>=y;i--)
#define all(x) x.begin(),x.end()
#define pb push_back
#define fi first
#define se second
#define mes(a,b) memset(a,b,sizeof a)
#define mp make_pair
#define dd(x) cout<<#x<<"="<<x<<" "
#define de(x) cout<<#x<<"="<<x<<"\n"
#define debug() cout<<"I love Miyamizu Mitsuha forever.\n"
const int inf=0x3f3f3f3f;
const int maxn=2e5+5;
int n,k;
ll dp[maxn][3];
vector<pii> v[maxn];
ll ans=0;
pii val[maxn];
ll prefix[maxn],suffix[maxn];

bool comp(const pii &s1,const pii &s2)
{
	return s1.fi>s2.fi||(s1.fi==s2.fi&&s1.se>s2.se);
	
}
ll getinit(int n)
{
	sort(val+1,val+1+n,comp);
	prefix[0]=0;
	rept(i,1,n) prefix[i]=max(prefix[i-1],val[i].se-val[i].fi);
	suffix[n+1]=0;
	for(int i=n;i>=1;i--) suffix[i]=max(suffix[i+1],val[i].se);
}

ll getval(int n,int cnt)
{
	if(cnt<=0) return 0;
	ll sum=0,ans=0;
	rept(i,1,min(n,cnt))
	{
		sum+=val[i].fi;
	}
	if(n<=cnt) return sum+prefix[n];
	ans=max(ans,sum+prefix[cnt]);
	ans=max(ans,sum-val[cnt].fi+suffix[cnt+1]);
	return ans;
}

void dfs(int id,int f)
{
	int cnt=0;
	rep(i,0,v[id].size())
		if(v[id][i].fi!=f) dfs(v[id][i].fi,id);
	rep(i,0,v[id].size())
	{
		if(v[id][i].fi!=f)
		{
			cnt++;
			val[cnt].fi=dp[v[id][i].fi][0]+v[id][i].se;
			val[cnt].se=dp[v[id][i].fi][1]+v[id][i].se;
		}
	}
	getinit(cnt);
	dp[id][0]=dp[id][1]=0;
	rept(i,1,cnt) dp[id][1]+=val[i].fi;
	rept(i,1,min(cnt,k-1)) dp[id][0]+=val[i].fi;
	dp[id][1]=max(dp[id][1],getval(cnt,k-1));
	ans=max(ans,getval(cnt,k));
	ans=max(ans,dp[id][1]);
}

void test()
{
	ans=0;
	cin>>n>>k;
	rept(i,1,n) v[i].clear();
	rep(i,1,n)
	{
		int a,b,d;
		cin>>a>>b>>d;
		v[a].pb(mp(b,d));
		v[b].pb(mp(a,d));
	}
	if(k==0)
	{
		cout<<"0\n";
		return ;
	}
	dfs(1,-1);
	cout<<ans<<"\n";
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int q;
	cin>>q;
	while(q--) test();
	return 0;
}