#include<cstdio>
#include<cstring>
const int N=100010,M=25,S=26;
int Case,n,m,q,i,j,l,r,g[N][S],f[M][M];char a[N],b[M];
inline void up(int&a,int b){a>b?(a=b):0;}
inline int cal(int l,int r){
  int i,j;
  for(i=0;i<=m;i++)for(j=0;j<=i;j++)f[i][j]=N;
  f[0][0]=l-1;
  for(i=0;i<m;i++)for(j=0;j<=i;j++){
    up(f[i+1][j],f[i][j]);
    if(f[i][j]<r)up(f[i+1][j+1],g[f[i][j]+1][b[i+1]]);
  }
  for(i=m;i;i--)for(j=i;j<=m;j++)if(f[j][i]<=r)return i;
  return 0;
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%s%s",a+1,b+1);
    n=strlen(a+1),m=strlen(b+1);
    for(i=1;i<=n;i++)a[i]-='a';
    for(i=1;i<=m;i++)b[i]-='a';
    for(j=0;j<S;j++)g[n+1][j]=n+1;
    for(i=n;i;i--){
      for(j=0;j<S;j++)g[i][j]=g[i+1][j];
      g[i][a[i]]=i;
    }
    scanf("%d",&q);
    while(q--)scanf("%d%d",&l,&r),printf("%d\n",r-l+1+m-2*cal(l,r));
  }
}