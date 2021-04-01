#include <bits/stdc++.h>
using namespace std;
long long a[20],x,l,r,dp0[20],cc[20][20];
map<array<int,10>,long long>dp[20][2];
array<int,10>state={0};
long long C(int n,int m)
{
    if(m<n-m) m=n-m;
    if(cc[n][m]!=-1)return cc[n][m];
    long long ans=1;
    for(int i=m+1;i<=n;i++)ans*=i;
    for(int i=1;i<=n-m;i++)ans/=i;
    return cc[n][m]=ans;
}
long long dfs(int len,bool maxi,bool f)
{
    if(dp[len][f].find(state)!=dp[len][f].end()&&maxi==0)return dp[len][f][state];
    if(!len)
    {
        for(int i=0;i<10;i++)if(i!=x&&state[i]>=state[x])return dp[len][f][state]=0;
        return dp[len][f][state]=1;
    }
    long long res=0,maxn=maxi?a[len]:9;
    if(f&&!maxi)
    {
        for(int i=0;i<=len;i++)
        {
            for(int i0=0;i0<=len-i;i0++)dp0[i0]=0;
            dp0[len-i]=C(len,i);
            for(int i0=0;i0<10;i0++)
            {
                if(i0==x)continue;
                if(state[x]+i<=state[i0])
                {
                    dp0[0]=0;
                    break;
                }
                for(int i1=0;i1<=len-i;i1++)
                {
                    for(int i2=1;i2<=min(i1,state[x]+i-state[i0]-1);i2++)
                    {
                        dp0[i1-i2]+=C(i1,i2)*dp0[i1];
                    }
                }
            }
            res+=dp0[0];
        }
        return dp[len][f][state]=res;
    }
    for(int i=0;i<=maxn;i++)
    {
        if(i||f)
        {
            if(i==x||state[i]+2<state[x]+len)
            {
                state[i]++;
                res+=dfs(len-1,maxi&&i==a[len],1);
                state[i]--; 
            }
        }
        else res+=dfs(len-1,maxi&&i==a[len],0);
    }
    return maxi?res:dp[len][f][state]=res;
}
long long div(long long tmp)
{
    int p=0;
    while(tmp)a[++p]=tmp%10,tmp/=10;
    long long res=0;
    res+=dfs(p,1,0);
    return res;
}
int main()
{
    memset(cc,-1,sizeof(cc));
    int T;
    scanf("%d",&T);
    while(T--)
    {
        for(int i=0;i<20;i++)for(int i1=0;i1<2;i1++)dp[i][i1].clear();
        scanf("%lld %lld %lld",&l,&r,&x);
        printf("%lld\n",div(r)-div(l-1));
    }    
    return 0;
}