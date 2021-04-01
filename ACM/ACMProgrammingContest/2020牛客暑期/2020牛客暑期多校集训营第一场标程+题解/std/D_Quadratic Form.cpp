#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 200;

#ifndef NO_MAIN

void add(int &x, int a) {
  x += a;
  if (x >= MOD) {
    x -= MOD;
  }
}

int inverse(int a) {
  return a == 1 ? 1
                : static_cast<uint64_t>(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

int normalize(int x) {
  x %= MOD;
  add(x, MOD);
  return x;
}

int aa[N][N], a[N][N + N], b[N];

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0, x; j < n; ++j) {
        scanf("%d", &x);
        a[i][j] = aa[i][j] = normalize(x);
        a[i][n + j] = i == j;
      }
    }
    for (int j = 0; j < n; ++j) {
      int pivot = j;
      while (pivot < n && !a[pivot][j]) {
        pivot++;
      }
      assert(pivot < n);
      for (int k = 0; k < n + n; ++k) {
        std::swap(a[j][k], a[pivot][k]);
      }
      {
        uint64_t t = inverse(a[j][j]);
        for (int k = 0; k < n + n; ++k) {
          a[j][k] = t * a[j][k] % MOD;
        }
      }
      for (int i = 0; i < n; ++i) {
        if (i != j && a[i][j]) {
          uint64_t t = a[i][j];
          for (int k = 0; k < n + n; ++k) {
            add(a[i][k], MOD - t * a[j][k] % MOD);
          }
        }
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        int result = 0;
        for (int k = 0; k < n; ++k) {
          add(result, static_cast<uint64_t>(aa[i][k]) * a[k][n + j] % MOD);
        }
        assert(result == (i == j));
      }
    }
    for (int i = 0, x; i < n; ++i) {
      scanf("%d", &x);
      b[i] = normalize(x);
    }
    int result = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        add(result,
            static_cast<uint64_t>(b[i]) * a[i][n + j] % MOD * b[j] % MOD);
      }
    }
    printf("%d\n", result);
  }
}
#endif
