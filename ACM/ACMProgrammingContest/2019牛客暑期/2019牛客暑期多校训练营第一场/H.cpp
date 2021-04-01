#include <bits/stdc++.h>

using Long = long long;

static const int D = 60;
static const int MOD = 1e9 + 7;

void add(int &x, int a) {
  x += a;
  if (x >= MOD) {
    x -= MOD;
  }
}

struct Basis {
  Basis()
  {
    std::fill(index.begin(), index.end(), -1);
  }

  bool update(Long x, int i) {
    for (int j = 0; j < D; ++j) {
      if (~index[j] && (x >> j & 1)) {
        x ^= basis[j];
      }
    }
    if (!x) {
      return true;
    }
    int j = __builtin_ctzll(x);
    assert(index[j] == -1);
    index[j] = i;
    basis[j] = x;
    return false;
  }

  std::array<int, D> index;
  std::array<Long, D> basis;
};

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<Long> a(n);
    for (int i = 0; i < n; ++i) {
      scanf("%lld", &a[i]);
    }
    Basis o;
    int nullity = 0;
    int two = 5e8 + 4;
    for (int i = 0; i < n; ++i) {
      if (o.update(a[i], i)) {
        nullity++;
        add(two, two);
      }
    }
    int result = 1LL * nullity * two % MOD;
    std::vector<Long> aa;
    for (int i : o.index) {
      if (~i) {
        aa.push_back(a[i]);
        a[i] = 0;
      }
    }
    Basis b;
    for (int i = 0; i < n; ++i) {
      b.update(a[i], i);
    }
    for (int i = 0; i < static_cast<int>(aa.size()); ++i) {
      Basis bb = b;
      for (int j = 0; j < static_cast<int>(aa.size()); ++j) {
        if (i != j) {
          bb.update(aa[j], j);
        }
      }
      if (bb.update(aa[i], i)) {
        add(result, two);
      }
    }
    printf("%d\n", result);
  }
}
