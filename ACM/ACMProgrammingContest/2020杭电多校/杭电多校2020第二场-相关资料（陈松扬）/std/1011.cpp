#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=300010;
int Case,n,i;
struct E{ll ok,eat;}a[N];
inline bool cmp(const E&a,const E&b){return a.ok<b.ok;}
int root,f[N],son[N][2];
int tagpc[N],tagcc[N];
ll tagpa[N],tagca[N],pre[N],cur[N];
int cnt,q[N];ll ans[N];
inline void tagpre(int x,int c,ll a){
  if(!x)return;
  pre[x]=pre[x]*c+a;
  tagpc[x]*=c;
  tagpa[x]=tagpa[x]*c+a;
}
inline void tagcur(int x,int c,ll a){
  if(!x)return;
  cur[x]=cur[x]*c+a;
  tagcc[x]*=c;
  tagca[x]=tagca[x]*c+a;
}
inline void push(int x){
  if(tagpc[x]!=1||tagpa[x]){
    tagpre(son[x][0],tagpc[x],tagpa[x]);
    tagpre(son[x][1],tagpc[x],tagpa[x]);
    tagpc[x]=1;
    tagpa[x]=0;
  }
  if(tagcc[x]!=1||tagca[x]){
    tagcur(son[x][0],tagcc[x],tagca[x]);
    tagcur(son[x][1],tagcc[x],tagca[x]);
    tagcc[x]=1;
    tagca[x]=0;
  }
}
inline void rotate(int x){
  int y=f[x],w=son[y][1]==x;
  son[y][w]=son[x][w^1];
  if(son[x][w^1])f[son[x][w^1]]=y;
  if(f[y]){
    int z=f[y];
    if(son[z][0]==y)son[z][0]=x;
    if(son[z][1]==y)son[z][1]=x;
  }
  f[x]=f[y];son[x][w^1]=y;f[y]=x;
}
inline void splay(int x,int o){
  while(f[x]!=o){
    int y=f[x];
    if(f[y]!=o){if((son[f[y]][0]==y)^(son[y][0]==x))rotate(x);else rotate(y);}
    rotate(x);
  }
  if(!o)root=x;
}
inline void insert(int x){
  int y=root,nxt=0,last=root;
  while(y){
    last=y;
    push(y);
    if(max(pre[y],a[x].ok)+a[x].eat<cur[y]){
      nxt=y;
      y=son[y][0];
    }else{
      y=son[y][1];
    }
  }
  splay(last,0);
  if(!nxt){
    son[x][0]=last;
    f[last]=x;
    pre[x]=cur[last];
    cur[x]=max(pre[x],a[x].ok)+a[x].eat;
    root=x;
    return;
  }
  splay(nxt,0);
  pre[x]=pre[nxt];
  cur[x]=max(pre[x],a[x].ok)+a[x].eat;
  int tmp=son[nxt][0];
  son[x][0]=tmp;
  son[nxt][0]=0;
  if(tmp)f[tmp]=x;
  son[x][1]=nxt;
  f[nxt]=x;
  root=x;
  pre[nxt]=cur[x];
  cur[nxt]=max(cur[nxt],a[x].ok)+a[x].eat;
  y=son[nxt][1];
  if(!y)return;
  int z=0;
  last=y;
  while(y){
    last=y;
    push(y);
    if(cur[y]<a[x].ok){
      z=y;
      y=son[y][1];
    }else{
      y=son[y][0];
    }
  }
  splay(last,nxt);
  if(!z){
    tagcur(last,1,a[x].eat);
    tagpre(son[last][1],1,a[x].eat);
    pre[last]=cur[nxt];
    return;
  }
  splay(z,nxt);
  tagcur(son[z][0],0,a[x].ok+a[x].eat);
  tagcur(son[z][1],1,a[x].eat);
  cur[z]=a[x].ok+a[x].eat;
  tagpre(son[z][0],0,a[x].ok+a[x].eat);
  tagpre(son[z][1],1,a[x].eat);
  pre[z]=a[x].ok+a[x].eat;
  z=son[z][1];
  last=0;
  while(z){
    last=z;
    z=son[z][0];
  }
  if(last){
    splay(last,0);
    pre[last]=a[x].ok+a[x].eat;
  }
}
void dfs(int x){
  if(!x)return;
  push(x);
  dfs(son[x][0]);
  cnt++;
  q[cnt]=x;
  ans[cnt]=cur[x];
  dfs(son[x][1]);
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%lld%lld",&a[i].ok,&a[i].eat);
    sort(a+1,a+n+1,cmp);
    root=1;
    pre[1]=0;
    cur[1]=a[1].ok+a[1].eat;
    for(i=1;i<=n;i++)tagpc[i]=tagcc[i]=1;
    for(i=2;i<=n;i++)insert(i);
    dfs(root);
    for(i=1;i<=n;i++)printf("%lld%c",ans[i],i<n?' ':'\n');
    for(cnt=i=0;i<=n;i++){
      f[i]=0;
      son[i][0]=son[i][1]=0;
      tagpc[i]=tagcc[i]=0;
      tagpa[i]=tagca[i]=pre[i]=cur[i]=0;
      q[i]=ans[i]=0;
    }
  }
}