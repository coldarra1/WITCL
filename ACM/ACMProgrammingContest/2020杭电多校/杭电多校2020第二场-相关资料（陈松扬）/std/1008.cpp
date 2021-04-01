#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200010,M=262157,K=N*21;
const ll inf=~0ULL>>1;
int Case,n,m,q,i,x;bool is[N];ll ans[N];
int g[M],G[M],v[K],nxt[K],ed;
int pa[N],pb[N];
struct P{int l,r,a;ll b;}a[N],b[N];
inline bool cmp(const P&a,const P&b){return a.a<b.a;}
void build(int x,int a,int b){
  g[x]=G[x]=0;
  if(a==b)return;
  int mid=(a+b)>>1;
  build(x<<1,a,mid),build(x<<1|1,mid+1,b);
}
void insp(int x,int a,int b,int c,int d,int p){
  if(c<=a&&b<=d){
    v[++ed]=p;nxt[ed]=g[x];g[x]=ed;
    return;
  }
  int mid=(a+b)>>1;
  if(c<=mid)insp(x<<1,a,mid,c,d,p);
  if(d>mid)insp(x<<1|1,mid+1,b,c,d,p);
}
void insq(int x,int a,int b,int c,int p){
  v[++ed]=p;nxt[ed]=G[x];G[x]=ed;
  if(a==b)return;
  int mid=(a+b)>>1;
  if(c<=mid)insq(x<<1,a,mid,c,p);else insq(x<<1|1,mid+1,b,c,p);
}
inline ll four(ll x){return x*x*x*x;}
void solve1(int l,int r,int dl,int dr){
  int m=(l+r)>>1,dm=dl,x=b[pb[m]].a;ll tmp=inf;
  for(int i=dl;i<=dr&&x>=a[pa[i]].a;i++){
    ll now=four(x-a[pa[i]].a)+a[pa[i]].b;
    if(now<tmp)tmp=now,dm=i;
  }
  if(tmp<ans[b[pb[m]].l])ans[b[pb[m]].l]=tmp;
  if(l<m)solve1(l,m-1,dl,dm);
  if(r>m)solve1(m+1,r,dm,dr);
}
void solve2(int l,int r,int dl,int dr){
  int m=(l+r)>>1,dm=dr,x=b[pb[m]].a;ll tmp=inf;
  for(int i=dr;i>=dl&&x<=a[pa[i]].a;i--){
    ll now=four(x-a[pa[i]].a)+a[pa[i]].b;
    if(now<tmp)tmp=now,dm=i;
  }
  if(tmp<ans[b[pb[m]].l])ans[b[pb[m]].l]=tmp;
  if(l<m)solve2(l,m-1,dl,dm);
  if(r>m)solve2(m+1,r,dm,dr);
}
inline void work(int g,int G){
  int ca=0,cb=0,i;
  for(;g;g=nxt[g])pa[++ca]=v[g];
  for(;G;G=nxt[G])pb[++cb]=v[G];
  if(!ca||!cb)return;
  for(i=1;i<=cb;i++)if(b[pb[i]].a>=a[pa[1]].a){
    solve1(i,cb,1,ca);
    break;
  }
  for(i=cb;i;i--)if(b[pb[i]].a<=a[pa[ca]].a){
    solve2(1,i,1,ca);
    break;
  }
}
void dfs(int x,int a,int b){
  work(g[x],G[x]);
  if(a==b){
    if(is[a]){
      if(ans[a]==inf)ans[a]=-1;
      printf("%lld\n",ans[a]);
    }
    return;
  }
  int mid=(a+b)>>1;
  dfs(x<<1,a,mid);
  dfs(x<<1|1,mid+1,b);
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    q=ed=0;
    for(i=1;i<=n;i++){
      scanf("%d%lld",&a[i].a,&a[i].b);
      a[i].l=1,a[i].r=m;
    }
    for(i=1;i<=m;i++){
      int op;
      scanf("%d",&op);
      is[i]=op==3;
      ans[i]=inf;
      if(op==1){
        n++;
        scanf("%d%lld",&a[n].a,&a[n].b);
        a[n].l=i,a[n].r=m;
      }else if(op==2){
        scanf("%d",&x);
        a[x].r=i;
      }else{
        q++;
        scanf("%d",&b[q].a);
        b[q].l=i;
      }
    }
    sort(a+1,a+n+1,cmp);
    sort(b+1,b+q+1,cmp);
    build(1,1,m);
    for(i=n;i;i--)insp(1,1,m,a[i].l,a[i].r,i);
    for(i=q;i;i--)insq(1,1,m,b[i].l,i);
    dfs(1,1,m);
  }
}