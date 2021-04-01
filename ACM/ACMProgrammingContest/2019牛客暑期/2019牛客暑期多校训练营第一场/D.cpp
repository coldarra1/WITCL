#include <bits/stdc++.h>

static const int MOD = 1e9 + 7;

void dfs(std::vector<int> &count, const std::vector<int> &a, int i, int x,
         int p) {
  if (i < static_cast<int>(a.size())) {
    dfs(count, a, i + 1, x, p);
    dfs(count, a, i + 1, x ^ a[i], -p);
  } else {
    count[x] += p;
  }
}

int main() {
  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    std::vector<int> count(1 << k);
    for (int i = 0; i < n; ++i) {
      std::vector<int> a(m);
      for (int j = 0; j < m; ++j) {
        scanf("%d", &a[j]);
      }
      dfs(count, a, 0, 0, 1);
    }
    for (int i = 0; i < k; ++i) {
      for (int msk = 0; msk < 1 << k; ++msk) {
        if (~msk >> i & 1) {
          auto &x0 = count[msk];
          auto &x1 = count[msk | 1 << i];
          int tmp = x0 - x1;
          x0 += x1;
          x1 = tmp;
        }
      }
    }
    int inv = 1 << m;
    int result = 0;
    int three = 1;
    for (int msk = 0; msk < 1 << k; ++ msk) {
      result ^= 1LL * three * (count[msk] / inv) % MOD;
      three = 3LL * three % MOD;
    }
    printf("%d\n", result);
  }
}
