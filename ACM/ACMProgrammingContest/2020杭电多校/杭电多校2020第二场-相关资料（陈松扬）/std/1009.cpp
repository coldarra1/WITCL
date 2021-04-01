#include<cstdio>
#include<cstring>
const int N=405,M=4000005;
int Case,n,m,q,i,j,o,x,y,sx,sy,xl,xr,yl,yr,len,a[N][N],v[N*N],POS,ans;
bool tag[N][N];
char op[M];
inline void umin(int&a,int b){a>b?(a=b):0;}
inline void umax(int&a,int b){a<b?(a=b):0;}
int main(){
  scanf("%d",&Case);
  while(Case--){
    scanf("%d%d%d",&n,&m,&q);
    for(i=1;i<=n;i++)for(j=1;j<=m;j++)scanf("%d",&a[i][j]);
    while(q--){
      scanf("%d%d%s",&sx,&sy,op);
      len=strlen(op);
      xl=n,xr=0,yl=m,yr=0;
      for(x=sx,y=sy,i=0;i<len;i++){
        umin(xl,x);
        umax(xr,x);
        umin(yl,y);
        umax(yr,y);
        if(op[i]=='L')x--;
        if(op[i]=='R')x++;
        if(op[i]=='D')y--;
        if(op[i]=='U')y++;
      }
      xl++,yl++;
      for(i=xl;i<=xr;i++)for(j=yl;j<=yr;j++)tag[i][j]=0;
      for(x=sx,y=sy,i=0;i<len;i++){
        if(op[i]=='L'){
          tag[x][y+1]^=1;
          x--;
        }
        if(op[i]=='R'){
          x++;
          tag[x][y+1]^=1;
        }
        if(op[i]=='D')y--;
        if(op[i]=='U')y++;
      }
      POS++;
      ans=0;
      for(i=xl;i<=xr;i++)for(o=0,j=yl;j<=yr;j++){
        o^=tag[i][j];
        if(!o)continue;
        if(v[a[i][j]]!=POS)v[a[i][j]]=POS,ans++;
      }
      printf("%d\n",ans);
    }
  }
}