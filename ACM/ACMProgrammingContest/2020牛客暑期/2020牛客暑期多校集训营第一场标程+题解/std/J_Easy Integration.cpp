#include <cassert>
#include <cstdio>
#include <vector>

const int N = 1000000;
const int MOD = 998244353;

static inline int inv(int a) {
  return a == 1 ? 1 : MOD - 1LL * (MOD / a) * inv(MOD % a) % MOD;
}

#ifndef NO_MAIN
int main() {
  std::vector<int> factorial(2 * N + 2);
  factorial[0] = 1;
  for (int i = 1; i <= 2 * N + 1; ++i) {
    factorial[i] = 1LL * factorial[i - 1] * i % MOD;
  }
  int n;
  while (scanf("%d", &n) == 1) {
    int inv_fact = inv(factorial[2 * n + 1]);
    assert(1LL * inv_fact * factorial[2 * n + 1] % MOD == 1);
    printf("%d\n", static_cast<int>(1LL * factorial[n] * factorial[n] % MOD *
                                    inv_fact % MOD));
  }
}
#endif