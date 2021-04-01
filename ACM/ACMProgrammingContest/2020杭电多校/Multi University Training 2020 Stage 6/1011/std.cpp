#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int P = 31607;
int add(int a, int b) { int r = a + b; return r < P ? r : r - P; }
int sub(int a, int b) { int r = a - b; return r < 0 ? r + P : r; }
int mul(int a, int b) { return a * b % P; }
int mod(int x) { x %= P; return x < 0 ? x + P : x; }
int inv[P];

struct vec { int x, y; int w; };
vec operator+(vec v1, vec v2) { return { v1.x + v2.x, v1.y + v2.y }; }
vec operator-(vec v1, vec v2) { return { v1.x - v2.x, v1.y - v2.y }; }
int operator*(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
int operator^(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }

const int N = 200001;
vec pa[N], pb[N], pc[N], pu[N], pv[N];

int main(void) {
    inv[1] = 1;
    for (int i = 2; i < P; ++i)
        inv[i] = mul(inv[P % i], P - P / i);

    int T; scanf("%d", &T);
    while (T--) {
        int n = 0; scanf("%d", &n);
        for (int i = 1; i <= n; ++i) {
            int u, v; 
            scanf("%d %d %d %d", &pa[i].x, &pa[i].y, &u, &v);
            assert(0 <= v && v < P);
            pa[i].w = mul(u, inv[v]);
        }

        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            int m = 0;
            for (int j = 1; j <= n; ++j) {
                if (j == i) continue;
                pb[++m] = pa[j] - pa[i]; pb[m].w = pa[j].w;
                pb[++m] = pa[i] - pa[j]; pb[m].w = 0;
            }
            vec dir = pb[1];
            auto pcmp = [&](vec v) { int x=v^dir; return x?x>0:v*dir>0; };
            auto scmp = [&](vec v1, vec v2) { int x=v1^v2; return x?x>0:v1*v1<v2*v2; };
            int t = partition(pb + 1, pb + m + 1, pcmp) - pb - 1;
            sort(pb + 1, pb + t + 1, scmp);
            sort(pb + t + 1, pb + m + 1, scmp);

            int ql = 1, qr = 1;
            for (int j = 1; j <= m / 2; ++j)
                ql = mul(ql, sub(1, pb[j].w));
            for (int j = m / 2 + 1; j <= m; ++j)
                qr = mul(qr, sub(1, pb[j].w));

            for (int l1 = 1, l2 = m / 2 + 1, r1 = l1, r2 = l2;
                l1 <= m / 2 && l2 <= m; l1 = r1, l2 = r2) {
                while (r1 <= m / 2 && (pb[r1] ^ pb[l1]) == 0) ++r1;
                while (r2 <= m && (pb[r2] ^ pb[l2]) == 0) ++r2;
                
                int pl = 1, pr = 1;
                for (int j = l1; j < r1; ++j)
                    pl = mul(pl, sub(1, pb[j].w));
                for (int j = l2; j < r2; ++j)
                    pr = mul(pr, sub(1, pb[j].w));

                ql = mul(ql, inv[pl]);
                qr = mul(qr, inv[pr]);

                int k = 1;
                pc[k] = pa[i], pc[k].w = pa[i].w;
                for (int j = l2; j < r2; ++j)
                    pc[++k] = pb[j] + pa[i], pc[k].w = pb[j].w;
                reverse(pc + 1, pc + k + 1);
                for (int j = l1; j < r1; ++j)
                    pc[++k] = pb[j] + pa[i], pc[k].w = pb[j].w;
                //assert(k <= 2000);
                for (int j = 1, t = 1; j <= k; ++j) {
                    pu[j] = { mul(mod(pc[j].x), mul(t, pc[j].w)), mul(mod(pc[j].y), mul(t, pc[j].w)) };
                    t = mul(t, sub(1, pc[j].w));
                }

                for (int j = k, t = 1; j >= 1; --j) {
                    pv[j] = { mul(mod(pc[j].x), mul(t, pc[j].w)), mul(mod(pc[j].y), mul(t, pc[j].w)) };
                    t = mul(t, sub(1, pc[j].w));
                }

                int sx = 0, sy = 0;
                for (int j = 1; j <= k; ++j) {
                    sx = add(sx, pv[j].x);
                    sy = add(sy, pv[j].y);
                }

                int sum = 0;
                for (int j = 1; j <= k; ++j) {
                    sx = sub(sx, pv[j].x);
                    sy = sub(sy, pv[j].y);
                    sum = add(sum, sub(mul(pu[j].x, sy), mul(pu[j].y, sx)));
                }

                int cnt = 0;
                for (int j = 1; j <= k; ++j) if (pc[j].w) cnt++;
                
                ans = add(ans, mul(inv[cnt], mul(sub(mul(qr, sub(1, ql)), mul(ql, sub(1, qr))), sum)));
                qr = mul(qr, pl);
                ql = mul(ql, pr);
            }        
        }
        ans = mul(ans, inv[2]);
        printf("%d\n", ans);
    }
    return 0;
}