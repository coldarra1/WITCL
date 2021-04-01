#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 7;

int T;
long long mod;
long long SS[maxn][maxn];
long long ans[maxn], trees[maxn], forests[maxn];
    
int power(int x, int times) {
    return SS[x][times];
}

long long C[maxn][maxn];
int main() {
    cin >> T >> mod;
    for (int i = 1; i < maxn; i++) {
        SS[i][0] = 1;
        for (int j = 1; j < maxn; j++)
            SS[i][j] = (long long)SS[i][j - 1] * i % mod;
    }

    for (int i = 0; i < maxn; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j] ;
            if (C[i][j] >= mod) C[i][j]-=mod;
        }
    }

    trees[1] = 1;
    for (int i = 2; i < maxn; i++) trees[i] = power(i, i - 2);

    forests[0] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j <= i; j++) {
            forests[i] = (forests[i] + trees[j] * C[i - 1][j - 1] % mod * forests[i - j]) % mod;
        }
    }

    ans[1] = 0;
    for (int i = 2; i < maxn; i++) {
        ans[i] = (ans[i] + (long long)C[i][2] % mod * forests[i - 2]) % mod;
        for (int j = 3; j <= i; j++) {
            ans[i] = (ans[i] + 2LL * C[i][2] % mod * C[i - 2][j - 2] % mod * power(j, j - 3) % mod * forests[i - j]) % mod;
        }

        if (i >= 3) {
            ans[i] = (ans[i] + 3LL * C[i][3] % mod * forests[i - 3]) % mod;
            for (int j = 4; j <= i; j++) {
                ans[i] = (ans[i] + 3LL * C[i][3] % mod * C[i - 3][j - 3] % mod * 3 % mod * power(j, j - 4) % mod * forests[i - j]) % mod;
            }
        }
    }

    while (T--) {
        int n;
        cin >> n;
        cout << (2LL * ans[n]) % mod << endl;
    }
    return 0;
}
