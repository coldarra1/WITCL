#include<cstdio>
const int MAX_N = 3005;
const int MOD = 998244353;
int n, m;
char s[MAX_N], t[MAX_N];
long long C[MAX_N][MAX_N];
void ADD(long long &x, long long v) {
    x += v;
    if(x >= MOD) x -= MOD;
}
void pre() {
    for(int i = 0;i < MAX_N; i++) {
        C[i][0] = 1;
        for(int j = 1;j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if(C[i][j] >= MOD) C[i][j] -= MOD;
        }
    }

}
long long dp[MAX_N][MAX_N];
void solve(){
    long long an = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] != '0') {
            for(int j = m; j <= n - i - 1; j++) {
                ADD(an, C[n - i - 1][j]);
            }
        }
    }
    for(int j = 0; j <= n; j++) {
        for(int i = 0; i <= m; i++) {
            dp[j][i] = 0;
        }
    }
    for(int i = m - 1; i >= 0; i--) {
        for(int j = n - 1; j >= 0; j--) {
            ADD(dp[j][i], dp[j + 1][i]);
            if(s[j] > t[i]) {
                ADD(dp[j][i], C[n - j - 1][m - i - 1]);
            }
            else if(s[j] == t[i]) {
                ADD(dp[j][i], dp[j + 1][i + 1]);
            }
        }
    }
    ADD(an, dp[0][0]);
    printf("%lld\n", an);
}
int main() {
    pre();
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        scanf("%s%s", s, t);
        solve();

    }
    return 0;
}
