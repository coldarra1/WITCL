#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
const int MAXN=100005;
struct Generating_function
{
    long long ki[4][7];//x y
    Generating_function()
    {
        memset(ki,0,sizeof(ki));
        ki[0][0]=1;
    }
    void init()
    {
        memset(ki,0,sizeof(ki));
        ki[0][0]=1;
    }
    void mult(long long a,long long b)
    {
        for(int i=3;i;--i)
        {
            for(int j=6;j;--j)
            {
                ki[i][j]+=a*ki[i-1][j-1]%mod;
                if(j>1)ki[i][j]+=b*ki[i-1][j-2]%mod;
                ki[i][j]%=mod;
            }
        }
    }
    void div(long long a,long long b)
    {
        for(int i=1;i<=3;++i)
        {
            for(int j=1;j<=6;++j)
            {
                ki[i][j]-=a*ki[i-1][j-1]%mod;
                if(j>1)ki[i][j]-=b*ki[i-1][j-2]%mod;
                ki[i][j]=(ki[i][j]%mod+mod)%mod;
            }
        }
    }
    long long get()
    {
        return (ki[3][5]+ki[3][6])%mod;
    }
}solve;
int fa[MAXN],a[MAXN],b[MAXN],x,n,u,v;
int findf(int x)
{
    return fa[x]==x?x:fa[x]=findf(fa[x]);
}
void unions(int x,int y)
{
    a[findf(y)]+=a[findf(x)];
    b[findf(y)]+=b[findf(x)];
    fa[findf(x)]=findf(y);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        solve.init();
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&x);
            fa[i]=i;
            a[i]=b[i]=0;
            if(x==1)++a[i];
            else ++b[i];
            solve.mult(a[i],b[i]);
        }
        printf("%lld\n",solve.get());
        for(int i=1;i<n;++i)
        {
            scanf("%d %d",&u,&v);
            solve.div(a[findf(u)],b[findf(u)]);
            solve.div(a[findf(v)],b[findf(v)]);
            unions(u,v);
            solve.mult(a[findf(u)],b[findf(u)]);
            printf("%lld\n",solve.get());
        }
    }
    return 0;
}
