#include<bits/stdc++.h>
using namespace std;
#define il inline
#define rg register
#define ll long long
#define CL(a,b) memset(a,b,sizeof a)
const int N=2e5+7,inf=0x3f3f3f3f;
char s[N];
int a[N];
int black[N],white[N];
int main()
{
    int n;
    scanf("%d",&n);
    scanf("%s",s);
    for(int i=0;i<n;i++)
        if(s[i]=='.')
        a[i+1]=0;
        else a[i+1]=1;
        int ans=inf;
    for(int i=1;i<=n;i++)
        if(a[i]==0)
        {
            white[i]=white[i-1]+1;
            black[i]=black[i-1];
        }
        else
        {
            black[i]=black[i-1]+1;
            white[i]=white[i-1];
        }
    for(int i=0;i<=n;i++)
        ans=min(black[i]+white[n]-white[i],ans);
        cout<<ans<<endl;
    return 0;
}
