#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <climits>
#include <cmath>
using namespace std;

int T,n;
set<int> dp[20][20];
string s="11451419191145141919";
int ans[5010];

void dfs(int l,int r)
{
    if (!dp[l][r].empty()) return;
    if (r-l+1<=4)
    {
        int t=stoi(s.substr(l-1,r-l+1));
        if (t<=5000) dp[l][r].insert(t);
    }
    for (int i=l;i<r;i++)
    {
        dfs(l,i);
        dfs(i+1,r);
        for (int x:dp[l][i])
        {
            for (int y:dp[i+1][r])
            {
                if (x+y<=5000) dp[l][r].insert(x+y);
                if (x*y<=5000) dp[l][r].insert(x*y);
            }
        }
    }
}

int main()
{
	freopen("in.txt","r",stdin);
	freopen("b.txt","w",stdout);
    ios::sync_with_stdio(0); cin.tie(0);
    memset(ans,-1,sizeof(ans));
    for (int i=1;i<=11;i++)
    {
        dfs(1,i);
        for (int x:dp[1][i])
        {
            if (ans[x]==-1) ans[x]=i;
        }
    }
    cin>>T;
    while (T--)
    {
        cin>>n;
        cout<<ans[n]<<'\n';
    }
    getchar(); getchar();
    return 0;
}
