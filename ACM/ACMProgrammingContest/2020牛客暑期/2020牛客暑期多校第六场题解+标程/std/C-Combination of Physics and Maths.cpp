#include <bits/stdc++.h>

const int N = 205;

int T, n, m, a[N][N];

int main() {
    for (scanf("%d", &T); T; T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                scanf("%d", &a[i][j]);
            }
        }
        double ans = 1;
        for (int j = 0; j < m; j++) {
            double sum = 0;
            for (int i = 0; i < n; i++) {
                sum += a[i][j];
                ans = std::max(ans, sum / a[i][j]);
            }
        }
        printf("%.8f\n", ans);
    }
    return 0;
}