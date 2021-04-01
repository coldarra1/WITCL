#include <bits/stdc++.h>

const int mod = 998244353;
const int N = 1e5 + 5;

int n, m, ans, a[N], inv[N], f[N];
bool vis[N];

int main() {
    scanf("%d%d", &n, &m);
    inv[1] = f[1] = 1;
    for (int i = 2; i <= n; i++) {
        inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
        f[i] = (f[i - 1] + inv[i - 1]) % mod;
    }
    f[1] = 0;
    for (; m; m--) {
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]); vis[i] = false;
        }
        ans = 0;
        for (int i = 1; i <= n; i++) {
            if (vis[i]) { continue; }
            int k = 0;
            for (int u = i; !vis[u]; u = a[u], k++) { vis[u] = true; }
            ans = (ans + 1ll * f[k] * k) % mod;
        }
        printf("%d\n", ans);
    }
    return 0;
}