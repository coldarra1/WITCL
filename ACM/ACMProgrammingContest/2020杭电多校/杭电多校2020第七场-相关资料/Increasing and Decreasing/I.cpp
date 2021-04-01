#include<cstdio>
#include<algorithm>
using namespace std;
int T,n,x,y,res,tot=0,ans[100005];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        tot=0;
        scanf("%d%d%d",&n,&x,&y);
        if(1ll*x*y<n||n<x+y-1)
        {
            printf("NO\n");
            continue;
        }
        printf("YES\n");
        res=0;
        while(1ll*y*(x-1)>=n-res-1&&res<n)
        {
            res++;
            ans[++tot]=res;
            x--;
        }
        for(int i=res+(n-res)%y;i>res;i--)ans[++tot]=i;
        if((n-res)%y)x--;
        res+=(n-res)%y;
        for(int i=1;i<=x;i++)
        {
            for(int j=res+y;j>res;j--)ans[++tot]=j;
            res+=y;
        }
        for(int i=1;i<n;i++)printf("%d ",ans[i]);
        printf("%d\n",ans[n]);
    }
    return 0;
 } 
