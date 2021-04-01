#include <bits/stdc++.h>

const int N = 1010;
typedef long long ll;

int c[N][N], d[N];
ll pre[N][N];
ll dp[N][N], sufpre[N][N], sufdp[N][N];

ll solve(){
    memset(c, 0, sizeof(c));
    memset(d, 0, sizeof(d));
    memset(pre, 0, sizeof(pre));
    memset(dp, 0, sizeof(dp));
    memset(sufpre, 0, sizeof(sufpre));
    memset(sufdp, 0, sizeof(sufdp));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++ i){
        for (int j = 1; j <= m; ++ j){
            scanf("%d", &c[i][j]);
            c[i][j] = -c[i][j];
        }
    }
    for (int i = 1; i <= m; ++ i){
        scanf("%d", &d[i]);
    }
    for (int i = 1; i <= n; ++ i){
        for (int j = 1; j <= m; ++ j){
            pre[i][j] = pre[i][j - 1] + c[i][j];
        }
    }
    for (int i = 1; i <= n; ++ i){
        sufpre[i][m] = pre[i][m];
        for (int j = m - 1; j >= 0; -- j){
            sufpre[i][j] = std::max(sufpre[i][j + 1], pre[i][j]);
        }
    }
    for (int i = 0; i <= m; ++ i){
        dp[1][i] = pre[1][i];
    }
    for (int i = 2; i <= n; ++ i){
        sufdp[i - 1][m] = dp[i - 1][m];
        for (int j = m - 1; j >= 0; -- j){
            sufdp[i - 1][j] = std::max(sufdp[i - 1][j + 1], dp[i - 1][j]);
        }
        for (int j = 0; j <= m; ++ j){
            dp[i][j] = std::max(dp[i - 1][j] + sufpre[i][j], sufdp[i - 1][j] + pre[i][j]);
        }
    }
    ll sum = 0, ans = 0;
    for (int i = 0; i <= m; ++ i){
        if (i){
            sum += d[i];
        }
        ans = std::max(ans, sum + dp[n][i]);
    }
    return ans;
}

int main(){
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: %lld\n", i, solve());
    }
    return 0;
}
