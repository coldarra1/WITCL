#include<cstdio>
typedef long long ll;
const int N=55;
int Case,n,m,i,j,x,cnt[N],nxt[N],e[N][N][4];ll ans;
void dfs(int x,int a,int b,int c,int d){
  if(x>m){
    ll tmp=1LL*a*b*c*d;
    if(tmp>ans)ans=tmp;
    return;
  }
  int num=cnt[x];
  if(!num){
    dfs(nxt[x],a,b,c,d);
    return;
  }
  for(int i=1;i<=num;i++)dfs(x+1,a+e[x][i][0],b+e[x][i][1],c+e[x][i][2],d+e[x][i][3]);
}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    for(i=1;i<=m;i++)cnt[i]=0;
    while(n--){
      scanf("%d",&x);
      cnt[x]++;
      for(j=0;j<4;j++)scanf("%d",&e[x][cnt[x]][j]);
    }
    x=m+1;
    for(i=m;i;i--){
      nxt[i]=x;
      if(cnt[i])x=i;
    }
    ans=0;
    dfs(1,100,100,100,100);
    printf("%lld\n",ans);
  }
}