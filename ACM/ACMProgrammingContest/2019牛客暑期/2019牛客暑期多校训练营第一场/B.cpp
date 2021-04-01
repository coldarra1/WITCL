#include <bits/stdc++.h>

static const int MOD = 1e9 + 7;

int inverse(int a)
{
  return a == 1 ? 1 : 1LL * (MOD - MOD / a) * inverse(MOD % a) % MOD;
}

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%d", &a[i]);
    }
    int result = 0;
    for (int i = 0; i < n; ++i) {
      int p = 2LL * a[i] % MOD;
      int aa = 1LL * a[i] * a[i] % MOD;
      for (int j = 0; j < n; ++j) {
        if (i != j) {
          p = 1LL * p * (1LL * a[j] * a[j] % MOD + MOD - aa) % MOD;
        }
      }
      (result += inverse(p)) %= MOD;
    }
    printf("%d\n", result);
  }
}
