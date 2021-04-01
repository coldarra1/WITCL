#include<bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;++i)
#define mp make_pair
#define pb push_back
#define st first
#define nd second
#define x0 fuckcjb
#define y0 fuckyzc
#define x1 fucksf
#define y1 fuckjsb
using namespace std;
typedef long long ll;
const int N=3;
int T,a[N][N],al;
int main(){
    for(scanf("%d",&T);T--;){
        al=0;
        rep(i,3)rep(j,3)scanf("%d",a[i]+j),al^=(a[i][j]-1);
        int ans=0;
        rep(x0,3)rep(y0,3){
            bool flag=1;
            rep(x1,3)if(x1!=x0)rep(y1,3)if(y1!=y0)
                if(al==((a[x0][y0]-1)^(a[x1][y1]-1)^a[3-x0-x1][3-y0-y1]^(a[3-x0-x1][3-y0-y1]-1))){
                    flag=0;break;
                }
            ans+=flag;
        }
        printf("%d\n",ans);

    }
}