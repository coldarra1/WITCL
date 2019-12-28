#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+7;
const ll inf=1e17;
int a,b,q;
ll s[N],t[N],x;
int binary(ll *p,int m)
{
    int l=1,r=m;
    while(l<=r)
    {
        int mid=(l+r)>>1;
        if(p[mid]<=x)
            l=mid+1;
        else
            r=mid-1;
    }
        return l;
}
int main()
{
    scanf("%d%d%d",&a,&b,&q);
    int j,k;
    for(int i=1;i<=a;i++)
        scanf("%lld",&s[i]);
    for(int i=1;i<=b;i++)
        scanf("%lld",&t[i]);
        s[0]=-1*inf,s[a+1]=inf;
        t[0]=-1*inf,t[b+1]=inf;
    for(int i=1;i<=q;i++)
    {
        ll ans=0;
        scanf("%lld",&x);
        j=binary(s,a);
        k=binary(t,b);
        ans=min(max(s[j],t[k])-x,x-min(s[j-1],t[k-1]));
        ans=min(ans,min(2*t[k]-s[j-1]-x,t[k]-2*s[j-1]+x));
        ans=min(ans,min(2*s[j]-t[k-1]-x,s[j]-2*t[k-1]+x));
        printf("%lld\n",ans);
    }
    return 0;
}
