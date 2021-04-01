#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
int dp[20][1000005],f[20][1000005],nxt[1000005],m,a,b,n,T;
ll ans=0,al,t;
ll gcd(ll a,ll b){return b==0?a:gcd(b,a%b);}
void cnt(int p,int k)
{
    for(int i=19;i>=0;i--)
    {
        if((1<<i)>k)continue;
        ans+=2ll*dp[i][p];
        k-=(1<<i);
        p=f[i+1][p];
    }
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&m,&a,&b,&n);
        ans=0;
        for(int i=0;i<n;i++)nxt[i]=(1ll*a*i+b)%n,dp[0][i]=(nxt[i]%2==0),f[0][i]=nxt[i];
        ans+=m+1;
        for(int i=1;i<20;i++)
        {
            for(int j=0;j<n;j++)
            {
                f[i][j]=f[i-1][f[i-1][j]];
                dp[i][j]=dp[i-1][j]+dp[i-1][f[i][j]];
            }
        }
        for(int i=0;i<2*m;i++)
        {
            if(i<=m)cnt((i%2==0)?nxt[i]:i,(i+1)/2);
            else cnt((i%2==0)?nxt[i]:i,(2*m-i+1)/2);
        }
        al=1ll*(m+1)*(m+1);
        t=gcd(ans,al);
        printf("%lld/%lld\n",ans/t,al/t);
    }
    return 0;
}
