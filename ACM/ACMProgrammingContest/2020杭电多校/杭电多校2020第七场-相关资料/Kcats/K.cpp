#include<cstdio>
#include<algorithm>
using namespace std;
int T,dp[105][105][105],p[105],n,ans=0,fac[105],invfac[105];
const int mod=1e9+7;
int mypow(int a,int b)
{
    int ans=1;
    while(b)
    {
        if(b&1)ans=1ll*ans*a%mod;
        a=1ll*a*a%mod;
        b>>=1;        
    }
    return ans;
}
int main()
{
    fac[0]=1;
    for(int i=1;i<=100;i++)fac[i]=1ll*fac[i-1]*i%mod;
    invfac[100]=mypow(fac[100],mod-2);
    for(int i=99;i>=0;i--)invfac[i]=1ll*invfac[i+1]*(i+1)%mod;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++)scanf("%d",&p[i]);
        ans=0;
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<=n;j++)dp[i][i][j]=0,dp[i][i-1][j]=1;
            if(p[i]==-1)for(int j=0;j<i;j++)dp[i][i][j]=1;
            else dp[i][i][p[i]-1]=1;
        }
        for(int i=0;i<=n;i++)dp[n+1][n][i]=1;
        for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)dp[i][j][n+1]=0;
        for(int l=2;l<=n;l++)
        {
            for(int i=1;i<=n-l+1;i++)
            {
                for(int j=0;j<i;j++)
                {
                    dp[i][i+l-1][j]=0;
                    for(int k=i;k<=i+l-1;k++)
                    {
                        if(p[k]==-1||p[k]==j+1)dp[i][i+l-1][j]=(1ll*dp[i][i+l-1][j]+1ll*dp[i][k-1][j]*dp[k+1][i+l-1][j+1]%mod*fac[l-1]%mod*invfac[k-i]%mod*invfac[i+l-1-k])%mod;
                    }
                }
            }
        }
        for(int i=0;i<=n;i++)ans=(ans+dp[1][n][i])%mod;
        printf("%d\n",ans);
    }
    return 0;
}
