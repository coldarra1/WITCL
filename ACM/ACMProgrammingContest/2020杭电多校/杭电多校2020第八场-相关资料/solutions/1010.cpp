//by Sshwy
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)

const int N=5005,P=998244353;
int pw(int a,int m){
    int res=1;
    while(m)m&1?res=1ll*res*a%P:0,a=1ll*a*a%P,m>>=1;
    return res;
}
int n,m,root,dist[N],fa[N],vis[N],sz[N],inv[N],use[N];
vector<int> g[N],T[N];
vector< pair<int,int> > e;

queue<int> q;
void bfs(){
    FOR(i,1,n)vis[i]=dist[i]=0;

    q.push(root);
    dist[root]=0;
    vis[root]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:g[u]){
            if(vis[v]){
                assert(dist[v]!=dist[u]);
                if(dist[v]>dist[u]){
                    assert(dist[v]==dist[u]+1);
                    e.pb({u,v});
                }
            }else {
                vis[v]=1;
                dist[v]=dist[u]+1;
                fa[v]=u;
                T[u].pb(v);
                q.push(v);
            }
        }
    }
}
void dfs(int u){
    sz[u]=1;
    for(int v:T[u])dfs(v),sz[u]+=sz[v];
}
long long f[N][N];
void go(){
    scanf("%d%d%d",&n,&m,&root);
    FOR(i,1,n)g[i].clear(), T[i].clear(), use[i]=0;
    e.clear();
    FOR(i,1,m){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].pb(v),g[v].pb(u);
    }
    bfs();
    assert(e.size() + n-1 == m);
    dfs(root);

    FOR(i,1,n)inv[i]=pw(i,P-2);
    int ans=1;

    for(auto x:e){
        int u=x.fi,v=x.se,z1,z2;
        vector<int> A={0},B={0};
        for(z1=u,z2=fa[v];z1!=z2;z1=fa[z1],z2=fa[z2]){
            A.pb(sz[z1]),B.pb(sz[z2]);
            use[z1]=use[z2]=1;
        }
        int la=A.size()-1,lb=B.size()-1;
        FOR(i,0,la)FOR(j,0,lb){
            if(i==0 && j==0)f[i][j]=1;
            else if(i==0)f[i][j]=f[i][j-1]*inv[B[j]]%P;
            else if(j==0)f[i][j]=f[i-1][j]*inv[A[i]+sz[v]]%P;
            else f[i][j]=(f[i-1][j]+f[i][j-1])*inv[A[i]+B[j]]%P;
        }
        ans=ans*1ll*f[la][lb]%P;
    }

    FOR(i,1,n)if(!use[i])ans=1ll*ans*inv[sz[i]]%P;
    FOR(i,1,n)ans=1ll*ans*i%P;

    printf("%d\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    FOR(i,1,t)go();
    return 0;
}
