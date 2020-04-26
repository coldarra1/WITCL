#include<stdio.h>
#define ll long long
using namespace std;
int a,b;
int bit[30];

int next(ll x)
{
    int sum=0,sum1=0;
    for(int i=0; i<=29; i++)
    {
        if((1<<i)&x)sum+=(1<<i),sum1+=1;
        if(((1<<i)&x)&&((1<<(i+1))&x)==0)
        {
            return x+(1<<(i+1))-sum+bit[sum1-1];
        }
    }
    return 0;
}

int last(int x)
{
    int tmp=~x;
    tmp=next(tmp);
    if(tmp==0)return x;
    return ~tmp;
}

int main()
{
    for(int i=1;i<=29;i++)bit[i]=bit[i-1]+(1<<i-1);
    int flag=0;
    while(~scanf("%d%d",&a,&b))
    {
        ll tmp=next(a)-last(a)-(next(b)-last(b));
        if(tmp>0)puts(">");
        else if(tmp==0)puts("=");
        else puts("<");
    }
}

