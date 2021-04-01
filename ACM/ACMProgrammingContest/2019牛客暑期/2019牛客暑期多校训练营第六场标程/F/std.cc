#include <bits/stdc++.h>
using namespace std;
const int N = 3005;
const int Q = 1e9 + 7;
int n , K , C[N][N];
int a[N] , s[N][N], f[N][N], cnt[N] , w[N];
bool vis[N];

inline int CC(int n, int m) {
    return n < m ? 0 : C[n][m];
}

int check(int end) {
    int res = 1;
    memset(w , -1 , sizeof(w));
    for (int i = end / K ; i < end && i * K + 1 < n ; ++ i) {
        // child in [max(end, i * K) + 1 , i * K + K] is not filled
        int id = max(end, i * K) + 1 - i * K;
        assert(1 <= id && id <= K);
        res = 1LL * res * f[i][id] % Q;
        w[a[i]] = s[i][id];
    }
    // Last unfilled node, ensure the value on this node is greater than before.
    res = 1LL * res * f[end][0] % Q;
    w[a[end]] = s[end][0];
    
    cnt[n] = 0;
    int tot = 0;
    for (int i = n - 1 ; i >= 0 ; -- i) {
        cnt[i] = cnt[i + 1] + vis[i + 1];
        if (~w[i]) {
            int x = i, S = w[i];
            res = 1LL * res * CC(cnt[x] - tot, S) % Q;
            tot += S;
        }
    }
    return res;
}

void work() {
    scanf("%d%d" , &n , &K);
    for (int i = 0 ; i < n ; ++ i) {
        scanf("%d" , a + i);
        -- a[i];
    }
    for (int i = n - 1 ; i >= 0 ; -- i) {
        // Last child index.
        int last = max(min(K, n - i * K - 1), 0);
        s[i][last + 1] = 0;
        f[i][last + 1] = 1;
        for (int j = last ; j >= 1 ; -- j) {
            int x = i * K + j;
            s[i][j] = s[i][j + 1] + s[x][0];
            f[i][j] = 1LL * f[i][j + 1] * f[x][0] % Q * CC(s[i][j], s[x][0]) % Q;
        }
        s[i][0] = s[i][1] + 1;
        f[i][0] = f[i][1];
    }
    memset(vis, 0 , sizeof(vis));
    int res = 1;
    for (int i = n - 1 ; i > 0 ; -- i) {
        vis[a[i]] = 1;
        res = (res + check(i)) % Q;
    }
    static int ca = 0;
    printf("Case #%d: %d\n" , ++ ca, (f[0][0] - res + Q + 1) % Q);
}

int main() {
    for (int i = 0 ; i < N ; ++ i) {
        for (int j = 0 ; j <= i ; ++ j) {
            C[i][j] = j == 0 ? 1 : (C[i - 1][j - 1] + C[i - 1][j]) % Q;
        }
    }

    int T;
    scanf("%d" , &T);
    while (T --) {
        work();
    }
}