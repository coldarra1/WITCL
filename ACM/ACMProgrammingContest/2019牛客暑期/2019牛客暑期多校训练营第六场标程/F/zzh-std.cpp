#include <bits/stdc++.h>

const int N = 3010;
const int moder = (int) 1e9 + 7;
typedef std::pair <int, int> pii;

int fac[N], inv[N], comb[N][N];
std::vector <int> e[N], event[N];
int a[N];
int dp[N], sz[N];
int fa[N];
bool vis[N];

void precalc(int u){
    sz[u] = dp[u] = 1;
    for (auto v : e[u]){
        precalc(v);
        sz[u] += sz[v];
        dp[u] = 1ll * dp[u] * dp[v] % moder;
    }
    dp[u] = 1ll * dp[u] * inv[sz[u]] % moder;
}

int solve(){
    for (int i = 0; i < N; ++ i){
        e[i].clear();
    }
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++ i){
        scanf("%d", &a[i]);
        fa[i] = (i + k - 2) / k;
        for (int j = -(k - 2); j <= 1; ++ j){
            if (k * i + j <= n){
                e[i].push_back(k * i + j);
            }
        }
    }
    precalc(1);
    for (int i = 1; i <= n; ++ i){
        dp[i] = 1ll * dp[i] * fac[sz[i]] % moder;
    }
    memset(vis, 0, sizeof(vis));
    int ans = 0;
    for (int i = 2; i <= n; ++ i){
        vis[a[i - 1]] = true;
        for (int j = 0; j <= n; ++ j){
            event[j].clear();
        }
        int prod = 1;
        for (int j = i; j <= n; ++ j){
            if (vis[a[fa[j]]]){
                event[a[fa[j]] + 1].push_back(sz[j]);
                prod = 1ll * prod * dp[j] % moder;
            }
        }
        int now = 0;
        for (int j = n; j >= 1; -- j){
            now += !vis[j];
            bool flag = true;
            for (auto u : event[j]){
                if (u > now){
                    prod = 0;
                    flag = false;
                    break;
                }
                prod = 1ll * prod * comb[now][u] % moder;
                now -= u;
            }
            if (!flag){
                break;
            }
        }
        ans += prod;
        ans -= ans >= moder ? moder : 0;
        for (int j = 0; j <= n; ++ j){
            event[j].clear();
        }
        prod = 1;
        for (int j = i; j <= n; ++ j){
            if (vis[a[fa[j]]]){
                int val = j == i ? std::max(a[j], a[fa[j]] + 1) : a[fa[j]] + 1;
                event[val].push_back(sz[j]);
                prod = 1ll * prod * dp[j] % moder;
            }
        }
        now = 0;
        for (int j = n; j >= 1; -- j){
            now += !vis[j];
            bool flag = true;
            for (auto u : event[j]){
                if (u > now){
                    prod = 0;
                    flag = false;
                    break;
                }
                prod = 1ll * prod * comb[now][u] % moder;
                now -= u;
            }
            if (!flag){
                break;
            }
        }
        ans -= prod;
        ans += ans < 0 ? moder : 0;
    }
    ans = (ans + 1) % moder;
    return ans;
}

int main(){
    fac[0] = 1;
    for (int i = 1; i < N; ++ i){
        fac[i] = 1ll * fac[i - 1] * i % moder;
    }
    inv[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = moder - 1ll * (moder / i) * inv[moder % i] % moder;
    }
    for (int i = 0; i < N; ++ i){
        comb[i][0] = 1;
        for (int j = 1; j <= i; ++ j){
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % moder;
        }
    }
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
