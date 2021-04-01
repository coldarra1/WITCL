#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int main() {
    long long n, k;
    long long KL = 1;
    cin >> n >> k;
    long long B = sqrt(max(n, k)) + 1;

    long long ans = n;
    for (long long i = 2; i <= min(B, k); i++) {

        long long NN = n / i;
        ans += NN;

        while (i * NN + 1 > n) NN--;
        if (NN >= 0) ans += NN;

        KL = i;
        ans %= mod;
    }
    if (KL == k) {
        cout << ((ans + k - 1) % mod + mod) % mod << endl;
        return 0;
    }

    for (long long i = 1; i <= n / KL + 3; i++) {

        long long KK = min(k, n / i);
        ans += max(KK - KL, 0LL);

        while (i * KK + 1 > n) KK--;
        ans += max(KK - KL, 0LL);
        ans %= mod;
    }

    cout << (ans + k - 1) % mod << endl;
    return 0;
}