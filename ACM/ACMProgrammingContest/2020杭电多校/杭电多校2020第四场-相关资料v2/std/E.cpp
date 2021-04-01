#include<bits/stdc++.h>
using namespace std;

const int N = 100005, mod = 1e9 + 7;
int f[N], n;
string s[N];

int solve() {
    cin >> n;
    for (int i = 1; i <= n; i ++) {
        cin >> s[i];
    }
    fill(f, f + n + 1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; i ++) {
        f[i] = f[i - 1];
        if (i >= 2 && s[i] != s[i - 1]) {
            f[i] = (f[i] + f[i - 2]) % mod;
        }
    }
    return f[n];
}

int main() {
    int Test;
    cin >> Test;
    for (int Case = 1; Case <= Test; Case ++) {
        printf("%d\n", solve());
    }
    return 0;
}