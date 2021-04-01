#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
#include <assert.h>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
const int MOD=998244353;
#define SZ 666666
ll f[3005][3005];
ll qp(ll a,ll b)
{
    ll x=1; a%=MOD;
    while(b)
    {
        if(b&1) x=x*a%MOD;
        a=a*a%MOD; b>>=1;
    }
    return x;
}
int T,n,x[SZ];
int main()
{
    f[0][0]=0;
    for(int i=1;i<=3000;++i)
    {
        f[0][i]=0;
        ll ri=qp(i+i,MOD-2);
        for(int a=1;a<=i;++a)
        {
            int b=i-a;
            f[a][b]=1;
            f[a][b]+=f[a-1][b]*(2*a-1);
            f[a][b]%=MOD;
            if(b) f[a][b]+=f[a][b-1]*(2*b+1);
            f[a][b]=f[a][b]%MOD*ri%MOD;
        }
//        ll tot=1;
//        for(int j=1;j<=i;++j)
//            tot=tot*(2*j)%MOD;
//        for(int a=0;a<=i;++a)
//            cout<<f[a][i-a]*tot%MOD<<",";
//        cout<<"\n";
    }
    scanf("%d",&T);
//if(T!=2000)return 0;

    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n+n+1;++i)
            scanf("%d",x+i);
        ll ans=0;
        for(int i=3;i<=n+n+1;i+=2)
//            cout<<i/2<<","<<n-i/2<<"|"<<f[i/2][n-i/2]<<"a\n",
            ans+=f[i/2][n-i/2]*(x[i]-x[i-1]),
            ans%=MOD;
        for(int i=2;i<=n+n+1;i+=2)
//            cout<<f[n-i/2+1][i/2-1]<<"b\n",
            ans+=f[n-i/2+1][i/2-1]*(x[i]-x[i-1]),
            ans%=MOD;
//        ans=ans*fm%MOD;
        ans=(ans%MOD+MOD)%MOD;
        printf("%lld\n",ans);
    }
}
