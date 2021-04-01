#include<cstdio>
typedef unsigned int U;
typedef unsigned long long ull;
const int N=405,M=7000005,P=1000000007;
int Case,n,m,lim,i,j,p[N*N],a[N][N],f[N][N],g[N][N],h[N][N],pre[N][N],suf[N][N];
int tot,l[M],r[M],sum[M],val[M];ull sw[M],weight[N*N];
U SX=335634763,SY=873658265,SZ=192849106,SW=746126501;
inline ull xorshift128(){
  U t=SX^(SX<<11);
  SX=SY;
  SY=SZ;
  SZ=SW;
  return SW=SW^(SW>>19)^t^(t>>8);
}
inline ull myrand(){return (xorshift128()<<32)^xorshift128();}
int ins(int x,int a,int b,int c){
  int y=++tot;
  val[y]=val[x]+1;
  sum[y]=(sum[x]+p[c])%P;
  sw[y]=sw[x]+weight[c];
  if(a==b)return y;
  int mid=(a+b)>>1;
  if(c<=mid)l[y]=ins(l[x],a,mid,c),r[y]=r[x];
  else l[y]=l[x],r[y]=ins(r[x],mid+1,b,c);
  return y;
}
inline bool bigger(int A,int B,int C,int D){
  if(sw[A]+sw[B]==sw[C]+sw[D])return 0;
  int a=1,b=lim,mid;
  while(a<b){
    mid=(a+b)>>1;
    if(sw[r[A]]+sw[r[B]]==sw[r[C]]+sw[r[D]]){
      b=mid;
      A=l[A];
      B=l[B];
      C=l[C];
      D=l[D];
    }else{
      a=mid+1;
      A=r[A];
      B=r[B];
      C=r[C];
      D=r[D];
    }
  }
  return val[A]+val[B]>val[C]+val[D];
}
inline int getmax(int x,int y){
  if(!x||!y)return x+y;
  return bigger(f[x>>9][x&511],h[x>>9][x&511],f[y>>9][y&511],h[y>>9][y&511])?x:y;
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    lim=n*n;
    for(i=1;i<=lim;i++)weight[i]=myrand();
    for(p[0]=i=1;i<=lim;i++)p[i]=1LL*p[i-1]*n%P*n%P;
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)scanf("%d",&a[i][j]);
    for(i=0;i<=n+1;i++)for(j=0;j<=n+1;j++)f[i][j]=g[i][j]=h[i][j]=pre[i][j]=suf[i][j]=0;
    for(i=1;i<=n;i++)for(j=1;j<=n;j++){
      f[i][j]=bigger(f[i-1][j],0,f[i][j-1],0)?f[i-1][j]:f[i][j-1];
      f[i][j]=ins(f[i][j],1,lim,a[i][j]);
    }
    for(i=n;i;i--)for(j=n;j;j--){
      h[i][j]=bigger(g[i+1][j],0,g[i][j+1],0)?g[i+1][j]:g[i][j+1];
      g[i][j]=ins(h[i][j],1,lim,a[i][j]);
    }
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)pre[i][j]=getmax(pre[i][j-1],i<<9|j);
    for(i=n;i;i--)for(j=n;j;j--)suf[i][j]=getmax(suf[i][j+1],i<<9|j);
    while(m--){
      int xl,xr,yl,yr,ans;
      scanf("%d%d%d%d",&xl,&xr,&yl,&yr);
      ans=getmax(pre[xr+1][yl-1],suf[xl-1][yr+1]);
      printf("%d\n",(sum[f[ans>>9][ans&511]]+sum[h[ans>>9][ans&511]])%P);
    }
    for(i=0;i<=tot;i++)l[i]=r[i]=sum[i]=val[i]=sw[i]=0;
    tot=0;
  }
}