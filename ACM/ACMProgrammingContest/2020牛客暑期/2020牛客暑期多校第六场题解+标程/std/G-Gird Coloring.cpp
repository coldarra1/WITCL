#include <bits/stdc++.h>

int T, n, m, k, x, y;

int main() {
    for (scanf("%d", &T); T; T--) {
        scanf("%d%d", &n, &k);
        if (k == 1 || 2 * (n + 1) * n % k) { printf("-1\n"); continue; }
        m = k % 2 ? k : k / 2;
        for (x = 1; x <= n; x++) {
            if (n % x == 0 && m % x == 0 && (n + 1) % (m / x) == 0) { break; }
        }
        y = m / x;
        for (int d = 0; d < 2; d++) {
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j < n; j++) {
                    int c = i / ((n + 1) / y) * x + (i + j) % x;
                    if (x == 1) { c = j / (n / x) * y + (i + j) % y; }
                    if (d == 1 && m < k) { c += m; }
                    printf("%d ", c + 1);
                }
                printf("\n");
            }
        }
    }
    return 0;
}