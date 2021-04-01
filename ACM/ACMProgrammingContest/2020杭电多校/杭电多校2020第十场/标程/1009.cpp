#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdint>
#include <cassert>
using namespace std;

#define long int64_t

inline double cov(long sx, long sy, long sxy, int n) {
    __int128_t res = __int128_t(1) * sxy * n - __int128_t(1) * sx * sy;
    return double(res) / n / n;
}

/*
inline double cov(long sx, long sy, long sxy, int n) {
    double res = 1. * sxy * n - 1. * sx * sy;
    if (-1e18 < res && res < 1e18) res = sxy * n - sx * sy;
    return res / n / n;
}
*/

int x[1 << 20], y[1 << 20];
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        long sx = 0, sy = 0, sx2 = 0, sy2 = 0, sxy = 0;
        int n; scanf("%d", &n);
        int rem = 0;
        for (int i = 1; i <= n; i++) {
            char op[5]; scanf("%s", op);
            if (op[0] == '1') {
                scanf("%d%d", x + i, y + i);
                sx += x[i]; sy += y[i];
                sx2 += 1ll * x[i] * x[i];
                sy2 += 1ll * y[i] * y[i];
                sxy += 1ll * x[i] * y[i];
                rem ++;
            } else if (op[0] == '2') {
                int i; scanf("%d", &i);
                sx -= x[i]; sy -= y[i];
                sx2 -= 1ll * x[i] * x[i];
                sy2 -= 1ll * y[i] * y[i];
                sxy -= 1ll * x[i] * y[i];
                rem --;
            } else assert(0);
            double dx = cov(sx, sx, sx2, rem);
            double dy = cov(sy, sy, sy2, rem);
            double cxy = cov(sx, sy, sxy, rem);
            double ans = (dx + dy + sqrt(max(0.0, pow(dx - dy, 2) + 4 * pow(cxy, 2)))) / 2;
            printf("%.12f\n", sqrt(2 * ans));
        }
    }
    return 0;
}