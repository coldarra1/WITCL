#include<cstdio>
const int N=55,K=15,inf=100000000;
int Case,n,m,i,j,x,y,z,g[N][N],d[N],f[K][N],v[N],ans;
void dfs(int m){
  int i,j,k;
  for(i=1;i<=n;i++)d[i]=inf,f[m][i]=v[i]=0;
  for(d[1]=0,i=1;i<=n;i++){
    k=0;
    for(j=1;j<=n;j++)if(!v[j])if(!k||d[j]<d[k])k=j;
    v[k]=1;
    for(j=1;j<=n;j++)if(!v[j]&&d[k]+g[k][j]<d[j]){
      d[j]=d[k]+g[k][j];
      f[m][j]=k;
    }
  }
  if(!m){
    if(ans<d[n])ans=d[n];
    return;
  }
  for(i=n;i!=1;i=j){
    j=f[m][i];
    k=g[i][j];
    g[i][j]=g[j][i]=inf;
    dfs(m-1);
    g[i][j]=g[j][i]=k;
  }
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)for(j=1;j<=n;j++)g[i][j]=i==j?0:inf;
    for(i=1;i<=n*(n-1)/2;i++){
      scanf("%d%d%d",&x,&y,&z);
      g[x][y]=g[y][x]=z;
    }
    ans=0;
    dfs(m);
    printf("%d\n",ans);
  }
}