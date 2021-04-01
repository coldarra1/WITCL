#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100010,M=200010;
int Case,n,m,i,j,x,y,a[N],q[N],g[N],v[M<<1],nxt[M<<1],ed,f[N],fa[N],wake[N];long long ans;
inline void add(int x,int y){v[++ed]=y;nxt[ed]=g[x];g[x]=ed;}
inline bool cmp(int x,int y){return a[x]>a[y];}
int F(int x){return f[x]==x?x:f[x]=F(f[x]);}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    for(ed=0,i=1;i<=n;i++){
      scanf("%d",&a[i]);
      q[i]=f[i]=i;
      g[i]=fa[i]=wake[i]=0;
    }
    while(m--)scanf("%d%d",&x,&y),add(x,y),add(y,x);
    sort(q+1,q+n+1,cmp);
    for(i=1;i<=n;i++){
      x=q[i];
      wake[x]=1;
      for(j=g[x];j;j=nxt[j]){
        y=v[j];
        if(!wake[y])continue;
        y=F(y);
        if(y==x)continue;
        fa[y]=f[y]=x;
      }
    }
    for(ans=0,i=1;i<=n;i++)ans+=a[i]-a[fa[i]];
    printf("%lld\n",ans);
  }
}