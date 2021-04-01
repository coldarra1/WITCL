#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1e9 + 7;
constexpr int maxn = 5000 + 7;

int b[maxn];
int f[maxn][maxn], g[maxn][maxn];

void add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int work() {
    int n;
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) scanf("%d", &b[i]);

    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    f[1][1] = 1;

    
    for (int i = 2; i <= n; i++) {
        // 0 - right
        // 1 - left 
        for (int j = 1; j < i; j++) {
            if (b[i] == 0) add(g[i][j + 1], f[i - 1][j]);
            else add(g[i][j], f[i - 1][j]);
        }

        if (b[i] == 0) {
            for (int j = 1; j <= i; j++) {
                add(f[i][j], f[i][j - 1]);
                add(f[i][j], g[i][j]);
            }
        }
        else {
            for (int j = i; j >= 1; j--) {
                add(f[i][j], f[i][j + 1]);
                add(f[i][j], g[i][j]);
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) 
        add(ans, f[n][i]);
    cout << ans << endl;
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        work();
    }
}