#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 64000;
bool ip[N]; int ps[N], pc;
void eulerian_sieve(int n) {
    fill_n(ip + 1, n, 1); pc = 0; ip[1] = 0;
    for (int i = 2; i <= n; ++i) {
        if (ip[i]) ps[++pc] = i;
        for (int j = 1; j <= pc && i * ps[j] <= n; ++j) {
            ip[i * ps[j]] = 0;
            if (i % ps[j] == 0) break;
        }
    }
}

int n, sq, w[N], c;
int g[N], h[N];

inline int id(int x) { return !x ? 0 : (x <= sq ? c + 1 - x : n / x); }

void cal_g(int n_) {
    n = n_; sq = sqrt(n_); c = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
        int v = w[++c] = n / l; r = n / v;
        g[c] = v - 1;
        h[c] = -1;
    }
    eulerian_sieve(2 * sq);
    while (ps[pc] > sq) pc--;
    for (int i = 1; i <= pc; ++i)
        for (int j = 1, p = ps[i]; 1ll * p * p <= w[j]; ++j)
            g[j] -= g[id(w[j] / p)] - g[id(ps[i - 1])];
}

int& get(int i, int j) {
    int& r = h[j];
    if (1ll * ps[i] * ps[i] > w[j])
        r = -(g[j] - g[id(ps[i - 1])]);
    if (w[j] < ps[i])
        r = 0;
    return r;
}

void cal_s(int t) {
    for (int i = pc; i >= t; --i) 
        for (int j = 1, p = ps[i]; p * p <= w[j]; ++j)
            h[j] = get(i + 1, j) - (1 + get(i + 1, id(w[j] / p)));
}

int pi(int n) { return g[id(n)]; }

int count(int n, int k) {
    if (1ll * k * k > n) {
        int res = n;
        int l = k + 1, r = n / (n / l), cnt = 0;
        cal_g(k);
        cnt -= pi(l - 1);
        cal_g(n);
        cnt += pi(r);
        res -= (n / l) * cnt;
        l = r + 1;
        for (; l <= n; l = r + 1) {
            r = n / (n / l);
            cnt = pi(r) - pi(l - 1);
            res -= (n / l) * cnt;
        }
        return res;
    }
    else {
        cal_g(n);
        int t = 1;
        while (t <= pc && ps[t] <= k) ++t;
        cal_s(t);
        int res = n;
        for (int l = 1, r; l <= n; l = r + 1) {
            r = n / (n / l);
            res += (n / l) * (get(t, id(r)) - get(t, id(l - 1)));
        }
        return res;
    }
}

int main(void) {
    int T; scanf("%d", &T);
    while (T--) {
        int n, k; scanf("%d%d", &n, &k);
        int ans;
        if (k >= n) ans = n;
        else
            ans = count(n, k);
        printf("%d\n", ans);
    }
    return 0;
}