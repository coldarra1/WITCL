#include <bits/stdc++.h>

int main() {
  int n, m, mod;
  while (scanf("%d%d%d", &n, &m, &mod) == 3) {
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
      b[a[i] - 1]++;
    }
    for (int i = m - 2; i >= 0; --i) {
      b[i] += b[i + 1];
    }
    std::sort(a.begin(), a.end(), std::greater<int>());
    std::sort(b.begin(), b.end(), std::greater<int>());
    if (a[0] != m || b[0] != n) {
      puts("0");
    } else {
      int result = 1;
      for (int i = 1; i < n; ++i) {
        result = 1LL * result * a[i] % mod;
      }
      for (int i = 1; i < m; ++i) {
        result = 1LL * result * b[i] % mod;
      }
      printf("%d\n", result);
    }
  }
}
