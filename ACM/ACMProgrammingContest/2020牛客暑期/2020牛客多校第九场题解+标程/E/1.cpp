#include<bits/stdc++.h>
using namespace std;
const int P=998244353;

long long Pow(long long a,long long p)
{
    static long long ret;
    for(ret=1;p;p>>=1,a=a*a%P)if(p&1)ret=ret*a%P;
    return ret;
}

int a,b,c,d,x,y;

map<int,int>A[2];
void Make_Map(int x,int id)
{
    A[id].clear();
    for(int i=2;i*i<=x;i++)
    {
        if(x%i)continue;
        int c=0;
        while(x%i==0)c++,x/=i;
        A[id][i]=c;
    }
    if(x>1)A[id][x]=1;
}

void Solve()
{
    Make_Map(x,0);
    Make_Map(y,1);
    long long ret=1;
    for(map<int,int>::iterator it=A[0].begin();it!=A[0].end();++it)
    {
        long long f=(*it).first,px=(*it).second,py=A[1][f];
        if(py==0)continue;
        long long ptot=0;
        for(int i=a;i<=b;i++)
        {
            long long ano=max(c-1ll,i*px/py);
            (ptot+=max(0ll,d-ano)*i*px)%=P-1;
        }
        for(int i=c;i<=d;i++)
        {
            long long ano=max(a-1ll,(i*py-1)/px);
            (ptot+=max(0ll,b-ano)*i*py)%=P-1;
        }
        (ret*=Pow(f,ptot))%=P;
    }
    printf("%lld\n",ret);
}

int main()
{
    scanf("%d%d%d%d%d%d",&a,&b,&c,&d,&x,&y);
    Solve();
    return 0;
}
