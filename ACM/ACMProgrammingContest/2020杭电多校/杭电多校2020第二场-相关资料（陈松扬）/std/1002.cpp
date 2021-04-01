#include<cstdio>
#include<algorithm>
using namespace std;
const int N=605,K=25,P=1000000007;
int Case,n,m,o,i,j,k,t,a[N];
struct E{
  int x,y;
  E(){}
  E(int _x,int _y){x=_x,y=_y;}
};
inline bool cmp(const E&a,const E&b){return a.x>b.x;}
struct Info{
  int cnt;E v[K*5];
  void clr(){cnt=0;}
  void add(int A,int B){v[++cnt]=E(A,B);}
  void fix(){
    sort(v+1,v+cnt+1,cmp);
    int i,j,k=0;
    for(i=1;i<=cnt;i=j){
      int tmp=0;
      for(j=i;j<=cnt&&v[i].x==v[j].x;j++)tmp=(tmp+v[j].y)%P;
      v[++k]=E(v[i].x,tmp);
      if(k>=m)break;
    }
    cnt=k;
  }
}f[2][N][3];
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++)scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(i=0;i<2;i++)for(j=0;j<=n;j++)for(k=0;k<3;k++)f[i][j][k].clr();
    f[1][1][0].add(0,1);
    f[1][1][1].add(0,2);
    for(i=o=1;i<n;i++,o^=1){
      for(j=0;j<=n;j++)for(k=0;k<3;k++)f[o^1][j][k].clr();
      for(j=0;j<=n;j++)for(k=0;k<3;k++){
        f[o][j][k].fix();
        int cnt=f[o][j][k].cnt;
        if(!cnt)continue;
        int base=(a[i+1]-a[i])*(j*2-k);
        for(t=1;t<=cnt;t++){
          int A=base+f[o][j][k].v[t].x,B=f[o][j][k].v[t].y;
          if(j+1>k)f[o^1][j+1][k].add(A,1LL*B*(j+1-k)%P);
          if(j>1)f[o^1][j-1][k].add(A,1LL*B*(j-1)%P);
          if(j*2>k)f[o^1][j][k].add(A,1LL*B*(j*2-k)%P);
          if(k<2){
            f[o^1][j+1][k+1].add(A,1LL*B*(2-k)%P);
            f[o^1][j][k+1].add(A,1LL*B*(2-k)%P);
          }
        }
      }
    }
    f[o][1][2].fix();
    for(i=1;i<=f[o][1][2].cnt&&i<=m;i++)printf("%d %d\n",f[o][1][2].v[i].x,(f[o][1][2].v[i].y%P+P)%P);
    for(;i<=m;i++)puts("-1");
  }
}