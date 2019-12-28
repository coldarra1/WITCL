#include<stdio.h>
const int MAXN=1e5+5,mod=1e9+7;
int a[MAXN];
int fib[MAXN],n;
int main()
{
    a[1]=1,a[2]=1;
    for(int i=3; i<=100000; i++)a[i]=(a[i-1]+a[i-2])%mod;
    scanf("%d%d%d",&n,&fib[1],&fib[2]);
    for(int i=3; i<=n; i++)fib[i]=(fib[i-1]+fib[i-2])%mod;
    for(int i=2; i<=n; i++)
    {
        int tmp=(fib[i]-fib[i-1]+mod)%mod;
        int ans=(fib[n]-(1ll*a[n-i+1]*tmp%mod)+mod)%mod;
        printf("%d",ans);
        if(i!=n)printf(" ");
    }
    printf("\n");
}
