#include<cstdio>
typedef long long ll;
const int N=100005,M=N+100000*2,K=20;
int Case,n,m,i,j,k,x,y,z,col[N],val[N],g[N],v[N<<1],nxt[N<<1],ed;
int st[N],en[N],dfn;
int G[N],V[M],W[M],NXT[M],ED;bool is[M];
ll ans[M],now[K];
int op[M];
int cnt[K][2];
int fc[N*2+1][K+1][2],fs[N*2+1][K+1][2],vis[N*2+1],POS;
inline void add(int x,int y){v[++ed]=y;nxt[ed]=g[x];g[x]=ed;}
inline void addop(int x,int y,int z){
  V[++ED]=y;W[ED]=z;NXT[ED]=G[x];G[x]=ED;
  is[ED]=ans[ED]=0;
}
void dfs(int x,int y){
  st[x]=++dfn;
  for(int i=g[x];i;i=nxt[i])if(v[i]!=y)dfs(v[i],x);
  en[x]=++dfn;
}
inline void apply(int o){
  int x=V[o],y=W[o],i,j,k;
  if(y<0){
    y=~y;
    //delete
    for(j=0;j<K;j++)cnt[j][y>>j&1]--;
    for(i=en[x];i;i-=i&-i)if(vis[i]==POS)for(j=0;j<K;j++)now[j]-=fs[i][j][y>>j&1^1]+fc[i][j][y>>j&1^1];
    for(i=st[x]-1;i;i-=i&-i)if(vis[i]==POS)for(j=0;j<K;j++)now[j]+=fs[i][j][y>>j&1^1];
    for(i=st[x];i<=dfn;i+=i&-i)for(j=0;j<K;j++)fc[i][j][y>>j&1]--,fs[i][j][y>>j&1]--;
    for(i=en[x];i<=dfn;i+=i&-i)for(j=0;j<K;j++)fc[i][j][y>>j&1]++;
  }else{
    //ins
    for(j=0;j<K;j++)cnt[j][y>>j&1]++;
    for(i=en[x];i;i-=i&-i)if(vis[i]==POS)for(j=0;j<K;j++)now[j]+=fs[i][j][y>>j&1^1]+fc[i][j][y>>j&1^1];
    for(i=st[x]-1;i;i-=i&-i)if(vis[i]==POS)for(j=0;j<K;j++)now[j]-=fs[i][j][y>>j&1^1];
    for(i=st[x];i<=dfn;i+=i&-i){
      if(vis[i]!=POS){
        vis[i]=POS;
        for(j=0;j<K;j++)for(k=0;k<2;k++)fc[i][j][k]=fs[i][j][k]=0;
      }
      for(j=0;j<K;j++)fc[i][j][y>>j&1]++,fs[i][j][y>>j&1]++;
    }
    for(i=en[x];i<=dfn;i+=i&-i){
      if(vis[i]!=POS){
        vis[i]=POS;
        for(j=0;j<K;j++)for(k=0;k<2;k++)fc[i][j][k]=fs[i][j][k]=0;
      }
      for(j=0;j<K;j++)fc[i][j][y>>j&1]--;
    }
  }
}
inline ll cal(){
  ll ret=0;
  for(int i=0;i<K;i++)ret+=(1LL*cnt[i][0]*cnt[i][1]-now[i])<<i;
  return ret;
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d",&n);
    for(dfn=ed=ED=i=0;i<=n;i++)g[i]=G[i]=0;
    for(i=1;i<=n;i++)scanf("%d",&col[i]);
    for(i=1;i<=n;i++)scanf("%d",&val[i]);
    for(i=1;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
    dfs(1,0);
    for(i=1;i<=n;i++)addop(col[i],i,val[i]);
    is[ED]=1;
    scanf("%d",&m);
    while(m--){
      scanf("%d%d%d",&x,&y,&z);
      addop(col[y],y,~val[y]);
      if(x==1)val[y]=z;else col[y]=z;
      addop(col[y],y,val[y]);
      is[ED]=1;
    }
    for(i=0;i<=dfn;i++){
      vis[i]=0;
      for(j=0;j<K;j++)for(k=0;k<2;k++)fc[i][j][k]=fs[i][j][k]=0;
    }
    op[0]=ED+1;
    for(i=1;i<=n;i++){
      POS=i;
      m=0;
      for(j=G[i];j;j=NXT[j])op[++m]=j;
      for(j=0;j<K;j++)now[j]=cnt[j][0]=cnt[j][1]=0;
      for(j=m;j;j--){
        apply(op[j]);
        ll tmp=cal();
        ans[op[j]]+=tmp;
        ans[op[j-1]]-=tmp;
      }
    }
    for(i=1;i<=ED;i++){
      ans[i]+=ans[i-1];
      if(is[i])printf("%lld\n",ans[i]);
    }
  }
}