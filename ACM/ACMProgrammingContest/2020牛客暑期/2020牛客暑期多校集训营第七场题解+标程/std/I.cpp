#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 7;

int T;
long long mod;
long long no_rings[maxn], GraphCnt[maxn], EdgeCnt[maxn], f[maxn], g[maxn];
long long SS[maxn][maxn];
    
int power(int x, int times) {
    return SS[x][times];
}

long long C[maxn][maxn];
int main() {
    scanf("%d%d", &T, &mod);

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

    no_rings[1] = no_rings[2] = 1;
    for (int i = 3; i < maxn; i++) {
        no_rings[i] = power(i, i - 2);
    }

    for (int i = 1; i < maxn; i++) {
        GraphCnt[i] = no_rings[i];
    }

    for (int i = 2; i < maxn; i++) {
        EdgeCnt[i] = 0;
        for (int j = 1; j <= i - 1; j++) {
            EdgeCnt[i] = (EdgeCnt[i] + C[i - 2][j - 1] * power(i - 1, i - j - 1) % mod * i % mod * (j * j) % mod) % mod;
        }
    }

    // f: # graph
    // g: # edge

    f[0] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j <= i; j++) {
            f[i] = (f[i] + GraphCnt[j] * f[i - j] % mod * C[i - 1][j - 1]) % mod;
            g[i] = (g[i] + C[i - 1][j - 1] * (EdgeCnt[j] * f[i - j] % mod + GraphCnt[j] * g[i - j] % mod)) % mod;
        }
    }

    while (T--) {
        int n;
        cin >> n;
        cout << g[n] << endl;
    }
    return 0;
}
