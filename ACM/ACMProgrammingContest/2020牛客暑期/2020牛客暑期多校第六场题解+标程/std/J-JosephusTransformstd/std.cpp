#include <bits/stdc++.h>

const int N = 1e3 + 5;

int n, q, lst[N], nxt[N];
std::vector<int> p, g[N];

std::vector<int> operator *(std::vector<int> p, std::vector<int> q) {
    std::vector<int> res(n);
    for (int i = 0; i < n; i++) {
		res[i] = p[q[i]];
    }
    return res;
}

int main() {
 	scanf("%d%d", &n, &q);
    p.resize(n);
    for (int i = 0; i < n; i++) {
        p[i] = i;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            nxt[i] = (i + 1) % n;
            lst[i] = (i - 1 + n) % n;
		}
        g[k].resize(n);
       	int u = n - 1, m;
        for (int i = 0; i < n; i++) {
            m = k % (n - i) + 1;
            for (; m; m--) { u = nxt[u]; }
            g[k][i] = u;
            nxt[lst[u]] = nxt[u];
            lst[nxt[u]] = lst[u];
        }
    }
    for (int k, x; q; q--) {
        scanf("%d%d", &k, &x);
        std::vector<int> f = g[k - 1];
        for (; x; x >>= 1, f = f * f) {
            if (x & 1) { p = f * p; }
		}
	}
    for (int i = 0; i < n; i++) {
        printf("%d ", p[i] + 1);
    } 
	return 0;
}