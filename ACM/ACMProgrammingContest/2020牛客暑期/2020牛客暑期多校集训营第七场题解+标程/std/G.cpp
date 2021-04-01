#include <bits/stdc++.h>
using namespace std;

const int maxn = 3000 + 7;

int n, mod;
long long step[maxn * maxn * 2], inv[maxn * maxn * 2];

int C(int a, int b) {
    assert(a >= 0 && a < maxn * maxn * 2);
    assert(b >= 0 && b <= a);
    return step[a] * inv[b] % mod * inv[a - b] % mod;
}
int f[maxn][maxn], g[maxn][maxn], h[maxn];
int w[maxn][maxn];

int main() {
    scanf("%d%d", &n, &mod);
    assert(mod > 2 * n * n);
    int N = 2 * n * n;
    step[0] = 1;
    for (int i = 1; i <= N; i++) step[i] = step[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i <= N; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    for (int i = 1; i <= N; i++) inv[i] = inv[i - 1] * inv[i] % mod;

    // cout << step[0] << ' ' << step[1] << ' ' << step[2] << endl;

    for (int i = 0; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            if (i == 0) { w[i][j] = 1; continue; }
            w[i][j] = w[i - 1][j];
            if (i < j) w[i][j] += w[i][j - 1];
            if (w[i][j] >= mod) w[i][j] -= mod;
        }
    }

    for (int i = 0; i < n; i++) {
        
        for (int j = 0; j <= n; j++) {
            if (i == 0) break;

            int &rt = g[i][j];
            int cnt = 2 * i - 1 + (i - 1) * (2 * n);
            rt = (long long)w[j][n] * h[i - 1] % mod * C(cnt + j + n, cnt) % mod;
            if (j != 0) rt = (rt + g[i][j - 1]) % mod;
        }
        
        if (i == 0) h[i] = 1;
        else {
            int &rt = h[i];
            rt = f[i - 1][i + 1];
            rt = rt + g[i][n];
            if (rt >= mod) rt -= mod;
        }

        for (int j = 2; j <= n; j++) {
            int &rt = f[i][j];
            if (i != 0) rt = f[i - 1][j];
            int coe = 0;
            if (j - 1 > i + 1) coe = f[i][j - 1];
            else coe = h[i];

            int cnt = i + (j - 1) * (2 * n + 1) - 2 * n;
            // cout << i << ' ' << j << ' ' << cnt << endl;
            rt = (rt + (long long)w[n][n] * coe % mod * C(cnt + 2 * n, 2 * n) % mod) % mod;
        }
    }

    cout << h[n - 1] << endl;
    return 0;
}
