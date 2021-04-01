#include <bits/stdc++.h>
using namespace std;

const int maxn = 22;

int n, kase, ans[5010];
char s[12] = {'.', '1', '1', '4', '5', '1', '4', '1', '9', '1', '9'};

int num[12][6];
set<int> dp[maxn][maxn];

void dfs (int l, int r)
{
    if (l > r) return;
    if (dp[l][r].size()) return;
    if (r - l + 1 <= 4 && num[(l - 1) % 10 + 1][r - l + 1] <= 5000) dp[l][r].insert (num[(l - 1) % 10 + 1][r - l + 1]);
    for (int i = l; i < r; i++)
    {
        dfs (l, i); dfs (i + 1, r);
        if (dp[l][i].size() && dp[i + 1][r].size())
            for (auto u : dp[l][i])
                for (auto v : dp[i + 1][r])
                {
                    if (u * v <= 5000) dp[l][r].insert (u * v);
                    if (u + v <= 5000) dp[l][r].insert (u + v);
                }
    }
}

int main ()
{
//	freopen("in.txt","r",stdin);
//	freopen("a.txt","w",stdout);
    for (int len = 1; len <= 4; len++)
        for (int i = 1; i <= 10; i++)
            num[i][len] = num[i][len - 1] * 10 + s[(i + len - 1 - 1) % 10 + 1] - '0';
    memset (ans, -1, sizeof ans);
    dfs (1, 12);
    for (int i = 1; i <= 12; i++)
    {
        for (auto it : dp[1][i])
        {
            if (ans[it] == -1)
                ans[it] = i;
        }
    }
    scanf("%d", &kase);
    while (kase--)
    {
        scanf("%d", &n);
        if (ans[n] != INT_MAX) printf("%d\n", ans[n]);
        else puts("-1");
    }
    return 0;
}
