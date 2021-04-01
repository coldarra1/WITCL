#include<cstdio>
#include<set>
#include<map>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=55,M=N*N+N+7,E=500005;
const ll inf=~0ULL>>1;
int Case,n,m,cnt,i,x,val[N*N];ll a[N],b[N],_c[N],ans;
set<int>all,which[N];
map<int,int>id;
int u[E],v[E],c[E],nxt[E];ll co[E];
int t,S,T,l,r,q[E],g[M],f[M];ll d[M];bool in[M];
inline ll cal(ll a,ll b,ll x){return a*x*x+b*x;}
inline set<int> extend(ll a,ll b){
  ll tmp=-(b/(a*2));
  tmp-=9;
  tmp=max(tmp,1LL);
  tmp=min(tmp,1LL*m);
  while(tmp<m&&cal(a,b,tmp)>cal(a,b,tmp+1))tmp++;
  ll l=tmp,r=tmp+1;
  set<int>ret;
  ret.clear();
  for(int i=1;i<=n;i++){
    if(l<1){
      ret.insert(r++);
      continue;
    }
    if(r>m){
      ret.insert(l--);
      continue;
    }
    if(cal(a,b,l)<cal(a,b,r))ret.insert(l--);else ret.insert(r++);
  }
  for(set<int>::iterator it=ret.begin();it!=ret.end();it++)all.insert(*it);
  return ret;
}
inline void add(int x,int y,int z,ll zo){
  u[++t]=x;v[t]=y;c[t]=z;co[t]=zo;nxt[t]=g[x];g[x]=t;
  u[++t]=y;v[t]=x;c[t]=0;co[t]=-zo;nxt[t]=g[y];g[y]=t;
}
inline void spfa(){
  int x,i;
  for(i=1;i<=T;i++)d[i]=inf,in[i]=0;
  d[S]=0;in[S]=1;l=r=E>>1;q[l]=S;
  while(l<=r){
    x=q[l++];
    if(x==T)continue;
    for(i=g[x];i;i=nxt[i])if(c[i]&&co[i]+d[x]<d[v[i]]){
      d[v[i]]=co[i]+d[x],f[v[i]]=i;
      if(!in[v[i]]){
        in[v[i]]=1;
        if(d[v[i]]<d[q[l]])q[--l]=v[i];else q[++r]=v[i];
      }
    }
    in[x]=0;
  }
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    all.clear();
    id.clear();
    for(i=1;i<=n;i++){
      scanf("%lld%lld%lld",&a[i],&b[i],&_c[i]);
      which[i]=extend(a[i],b[i]);
    }
    cnt=0;
    for(set<int>::iterator it=all.begin();it!=all.end();it++){
      val[++cnt]=*it;
      id[*it]=cnt;
    }
    S=0,T=n+cnt+1;
    for(i=0,t=1;i<=T;i++)g[i]=0;
    for(i=1;i<=n;i++)add(S,i,1,0);
    for(i=1;i<=cnt;i++)add(n+i,T,1,0);
    for(i=1;i<=n;i++)for(set<int>::iterator it=which[i].begin();it!=which[i].end();it++)add(i,n+id[*it],1,cal(a[i],b[i],*it)+_c[i]);
    ans=0;
    for(i=1;i<=n;i++){
      spfa();
      ans+=d[T];
      printf("%lld%c",ans,i<n?' ':'\n');
      for(x=T;x!=S;x=u[f[x]])c[f[x]]--,c[f[x]^1]++;
    }
  }
}