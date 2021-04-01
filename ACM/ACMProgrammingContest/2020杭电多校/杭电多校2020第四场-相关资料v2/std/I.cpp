#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

template<class T> void read(T &x) {
    int f = 0; x = 0; char ch = getchar();
    for ( ; !isdigit(ch); ch = getchar()) f |= (ch == '-');
    for ( ; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
    if (f) x = -x;
}

const int N = 1000005, mod = 1e9 + 7;
int fac[N], rev[N], sz[N], ans[N], fa[N];
int n, m, res;

int power(int x, int p) {
    int res = 1;
    for ( ; p; p >>= 1, x = (ll) x * x % mod) {
        if (p & 1) res = (ll) res * x % mod;
    }
    return res;
}

void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; i ++) {
        fac[i] = (ll) fac[i - 1] * i % mod;
    }
    rev[n] = power(fac[n], mod - 2);
    for (int i = n; i >= 1; i --) {
        rev[i - 1] = (ll) rev[i] * i % mod;
    }
}

int C(int n, int m) {
    if (m < 0 || n < m) return 0;
    return (ll) fac[n] * rev[m] % mod * rev[n - m] % mod;
}

void add(int &x, int y) {
    x = (x + y >= mod ? x + y - mod : x + y);
}

int solve() {
    read(n);
    read(m);
    for (int i = 2; i <= n; i ++) {
        read(fa[i]);
        sz[i] = 0;
    }
    int p = (m - 1) / 2 - 1;
    int sum = (p >= 0 ? C(n - 1, m - 1) : 0);
    for (int i = 1; i <= n - 1; i ++) {
        int delta = (ll) C(i - 2, p) * C(n - i, m - 2 - p) % mod;
        add(sum, mod - delta);
        ans[i] = (ll) i * sum % mod;
    }
    for (int i = 1; i * 2 <= n; i ++) {
        add(ans[i], ans[n - i]);
        if (m % 2 == 0) {
            int c = (ll) C(i, m / 2) * C(n - i, m / 2) % mod;
            ans[i] = (ans[i] + (ll) c * (m / 2)) % mod;
        }
    }
    res = 0;
    for (int u = n; u >= 2; u --) {
        sz[u] ++;
        sz[fa[u]] += sz[u];
        add(res, ans[min(sz[u], n - sz[u])]);
    }
    return res;
}

int main() {
    int Test;
    read(Test);
    init(1000000);
    for (int Case = 1; Case <= Test; Case ++) {
        printf("%d\n", solve());
    }
    return 0;
}