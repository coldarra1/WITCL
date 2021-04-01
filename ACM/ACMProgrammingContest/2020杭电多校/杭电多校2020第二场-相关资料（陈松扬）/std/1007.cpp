#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=20005,M=25;
int Case,n,m,i,x,y,A,B,g[N],v[N<<1],a[N<<1],b[N<<1],nxt[N<<1],ed,size[N];
ll f[N][M],h[N],l,r,mid,ans;
inline void up(ll&a,ll b){a>b?(a=b):0;}
void dfs(int x,int y){
  size[x]=f[x][0]=0;
  for(int i=g[x];i;i=nxt[i]){
    int u=v[i];
    if(u==y)continue;
    dfs(u,x);
    int A=a[i],B=b[i],pre=size[x],cur=size[u],now=min(pre+cur+1,m);
    for(int j=0;j<=now;j++)h[j]=mid+1;
    for(int j=0;j<=pre;j++)for(int k=0;k<=cur&&j+k<=m;k++){
      if(f[x][j]+f[u][k]+A<=mid)up(h[j+k+1],max(f[x][j],f[u][k]+A));
      if(f[x][j]+f[u][k]+B<=mid)up(h[j+k],max(f[x][j],f[u][k]+B));
    }
    size[x]=now;
    for(int j=0;j<=now;j++)f[x][j]=h[j];
  }
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    l=r=0;
    for(ed=i=0;i<=n;i++)g[i]=0;
    for(i=1;i<n;i++){
      scanf("%d%d%d%d",&x,&y,&A,&B);
      v[++ed]=y;a[ed]=A;b[ed]=B;nxt[ed]=g[x];g[x]=ed;
      v[++ed]=x;a[ed]=A;b[ed]=B;nxt[ed]=g[y];g[y]=ed;
      r+=max(A,B);
    }
    while(l<=r){
      mid=(l+r)>>1;
      dfs(1,0);
      if(f[1][m]<=mid)r=(ans=mid)-1;else l=mid+1;
    }
    printf("%lld\n",ans);
  }
}