#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
mt19937 rnd(time(NULL));

const ll INF = 1e18;
const int N = 2005, M = 200005, bas = M / 2;
struct node { int ty, w, v; } a[N<<1];
int n, m, lim, L, R;
ll F[M], G[M];

void cmax(ll &x, ll y){
    if (y > x) x = y;
}

ll solve() {
    cin >> n >> m;
    for (int i = 1; i <= n + m; i ++) {
        cin >> a[i].w >> a[i].v;
        a[i].ty = (i <= n ? 1 : -1);
    }
    shuffle(a + 1, a + n + m + 1, rnd);
    lim = sqrt(n + m) * 1000 * 2;
    ll *f = F + bas, *g = G + bas;
    f[L = R = 0] = 0;
    for (int i = 1; i <= n + m; i ++) {
        if (a[i].ty == 1) {
            int nR = min(R + a[i].w, lim);
            for (int j = L; j <= R; j ++) {
                g[j] = f[j];
            }
            for (int j = R + 1; j <= nR; j ++) {
                g[j] = -INF;
            }
            for (int j = L; j <= nR - a[i].w; j ++) {
                cmax(g[j + a[i].w], f[j] + a[i].v);
            }
            R = nR;
        }
        else {
            int nL = max(L - a[i].w, -lim);
            for (int j = L; j <= R; j ++) {
                g[j] = f[j];
            }
            for (int j = nL; j <= L - 1; j ++) {
                g[j] = -INF;
            }
            for (int j = nL + a[i].w; j <= R; j ++) {
                cmax(g[j - a[i].w], f[j] + a[i].v);
            }
            L = nL;
        }
        swap(f, g);
    }
    return f[0];
}

int main() {
    int Test;
    cin >> Test;
    for (int Case = 1; Case <= Test; Case ++) {
        printf("%lld\n", solve());
    }
    return 0;
}