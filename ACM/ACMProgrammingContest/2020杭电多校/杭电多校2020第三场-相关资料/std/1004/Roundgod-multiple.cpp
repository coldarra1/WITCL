#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
int T,n,p,a[MAXN];
int s[MAXN];
int last[MAXN],dp[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&p);
        for(int i=1;i<=n;i++) 
        {
            scanf("%d",&a[i]);
            a[i]=a[i]%p;
        }
        memset(last,-1,sizeof(last));
        dp[0]=0;
        last[0]=0;
        for(int i=1;i<=n;i++)
        {
            s[i]=(s[i-1]+a[i])%p;
            dp[i]=dp[i-1];
            if(last[s[i]]!=-1) dp[i]=max(dp[i],dp[last[s[i]]]+1);
            last[s[i]]=i;
        }
        printf("%d\n",dp[n]);
    }
    return 0;
}