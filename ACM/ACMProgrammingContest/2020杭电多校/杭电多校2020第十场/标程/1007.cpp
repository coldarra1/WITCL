#include <bits/stdc++.h>
using namespace std;

const int threshold = 10000000;
unsigned long long k1, k2;

const int maxn = 10000000 + 7;

int a[maxn], b[maxn];

unsigned long long f() {
    unsigned long long k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void gen(int n, unsigned long long _k1, unsigned long long _k2) {
    k1 = _k1;
    k2 = _k2;
    for (int i = 1; i <= n; i++) {
        a[i] = f() % threshold + 1;
        b[i] = f() % threshold + 1;
    }
}

int main() {
    int n, m;
    while (cin >> n >> m >> k1 >> k2) {
        gen(n, k1, k2);
        for (int i = 1; i <= n; i++) b[i] += a[i];


        sort(a + 1, a + n + 1, greater<int>());
        sort(b + 1, b + n + 1, greater<int>());

        int p = 1, q = 0;

        long long cur = a[1];
        long long ans = a[1];
        for (int i = 2; i <= m; i++) {
            long long cur1 = -(1LL << 60);
            long long cur2 = -(1LL << 60);
            if (p < n) cur1 = a[p + 1];
            if (p >= 1 && q < n) cur2 = b[q + 1] - a[p];

            if (cur1 > cur2) {
                p++;
                cur += cur1;
            }
            else {
                p--;
                q++;
                cur += cur2;
            }
            ans ^= cur;
        }
        cout << ans << endl;
    }
    return 0;
}