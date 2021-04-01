#include<cstdio>
#include<algorithm>
using namespace std;
typedef unsigned int U;
typedef long long ll;
const int N=500010,K=30;
const U inf=~0U;
int Case,n,m,i,j,last,op,x,y,A,B,C,D,col[N],g[N],v[N<<1],nxt[N<<1],ed;
int f[N],d[N],size[N],son[N],top[N],loc[N],q[N],dfn;
U w[N][K],val[1111111][K],tmp[K];
U SX=335634763,SY=873658265,SZ=192849106,SW=746126501;
inline U xorshift128(){
  U t=SX^(SX<<11);
  SX=SY;
  SY=SZ;
  SZ=SW;
  return SW=SW^(SW>>19)^t^(t>>8);
}
inline void add(int x,int y){v[++ed]=y;nxt[ed]=g[x];g[x]=ed;}
void dfs1(int x,int y){
  f[x]=y,d[x]=d[y]+1,size[x]=1;
  for(int i=g[x];i;i=nxt[i]){
    int u=v[i];
    if(u==y)continue;
    dfs1(u,x);
    size[x]+=size[u];
    if(size[u]>size[son[x]])son[x]=u;
  }
}
void dfs2(int x,int y){
  q[loc[x]=++dfn]=x;
  top[x]=y;
  if(son[x])dfs2(son[x],y);
  for(int i=g[x];i;i=nxt[i])if(v[i]!=f[x]&&v[i]!=son[x])dfs2(v[i],v[i]);
}
inline void up(int x){for(int i=0;i<K;i++)val[x][i]=min(val[x<<1][i],val[x<<1|1][i]);}
void build(int x,int a,int b){
  if(a==b){
    int o=col[q[a]];
    for(int i=0;i<K;i++)val[x][i]=w[o][i];
    return;
  }
  int mid=(a+b)>>1;
  build(x<<1,a,mid),build(x<<1|1,mid+1,b);
  up(x);
}
void change(int x,int a,int b,int c,int p){
  if(a==b){
    for(int i=0;i<K;i++)val[x][i]=w[p][i];
    return;
  }
  int mid=(a+b)>>1;
  if(c<=mid)change(x<<1,a,mid,c,p);else change(x<<1|1,mid+1,b,c,p);
  up(x);
}
inline void umin(U&a,U b){a>b?(a=b):0;}
void ask(int x,int a,int b,int c,int d){
  if(c<=a&&b<=d){
    for(int i=0;i<K;i++)umin(tmp[i],val[x][i]);
    return;
  }
  int mid=(a+b)>>1;
  if(c<=mid)ask(x<<1,a,mid,c,d);
  if(d>mid)ask(x<<1|1,mid+1,b,c,d);
}
inline ll estimate(int x,int y){
  for(int i=0;i<K;i++)tmp[i]=inf;
  for(;top[x]!=top[y];x=f[top[x]]){
    if(d[top[x]]<d[top[y]])swap(x,y);
    ask(1,1,n,loc[top[x]],loc[x]);
  }
  if(d[x]<d[y])swap(x,y);
  ask(1,1,n,loc[y],loc[x]);
  ll ret=0;
  for(int i=0;i<K;i++)ret+=tmp[i];
  return ret;
}
int main(){
  for(i=1;i<N;i++)for(j=0;j<K;j++)w[i][j]=xorshift128();
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    for(ed=dfn=last=i=0;i<=n;i++)g[i]=f[i]=d[i]=size[i]=son[i]=0;
    for(i=1;i<=n;i++)scanf("%d",&col[i]);
    for(i=1;i<n;i++)scanf("%d%d",&x,&y),add(x,y),add(y,x);
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    while(m--){
      scanf("%d%d%d",&op,&A,&B);
      A^=last,B^=last;
      if(op==1)change(1,1,n,loc[A],B);
      else{
        scanf("%d%d",&C,&D);
        C^=last,D^=last;
        ll E=estimate(A,B),F=estimate(C,D);
        //printf(">> %.15f %.15f\n",(((double)(1ULL<<32))*K)/E-1,(((double)(1ULL<<32))*K)/F-1);
        if(E<F){
          puts("Yes");
          last++;
        }else puts("No");
      }
    }
  }
}