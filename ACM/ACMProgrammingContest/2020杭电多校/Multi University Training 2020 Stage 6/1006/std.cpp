#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9+7;
const int maxn = 1e5+10;

int n,m;ll ans=0;
int zero=0,one=0;
vector<pair<int,ll>>G[maxn];
int dp[maxn][2],col[maxn],f[maxn];

void dfs(int u,int f){
    dp[u][0]=dp[u][1]=0;
    dp[u][col[u]]++;
    for(auto it:G[u]){
        int v=it.first;
        if(v==f)continue;
        dfs(v,u);
        dp[u][0]+=dp[v][0];
        dp[u][1]+=dp[v][1];
    }
    for(auto it:G[u]){
        int v=it.first;
        if(v==f)continue;
        ans=(ans+1ll*dp[v][0]*(one-dp[v][1])%mod*it.second)%mod;
        ans=(ans+1ll*dp[v][1]*(zero-dp[v][0])%mod*it.second)%mod;
    }
}

int find(int x){return f[x]==x?x:(f[x]=find(f[x]));}

int main(){
    //freopen("./data/1.in","r",stdin);
    int T;cin>>T;
    while(T--){
        ans=0,zero=one=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)dp[i][0]=dp[i][1]=0,G[i].clear();
        for(int i=1;i<=n;i++)scanf("%d",&col[i]),f[i]=i;
        for(int i=1;i<=n;i++){
            if(col[i])one++;
            else zero++;
        }
        ll val=1;
        for(int i=1;i<=m;i++){
            int u,v;scanf("%d%d",&u,&v);
            val=val*2%mod;
            int fu=find(u),fv=find(v);
            if(fu==fv)continue;
            f[fu]=fv;
            G[u].push_back(make_pair(v,val));
            G[v].push_back(make_pair(u,val));
        }
        dfs(1,-1);
        printf("%lld\n",ans);
    }
}
