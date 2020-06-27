#include <bits/stdc++.h>

using namespace std;

const int md = 998244353;

inline void add(int &a, int b) {
  a += b;
  if (a >= md) a -= md;
}

inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) a += md;
}

inline int mul(int a, int b) {
  return (int) ((long long) a * b % md);
}

inline int power(int a, long long b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

inline int inv(int a) {
  a %= md;
  if (a < 0) a += md;
  int b = md, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= t * a; swap(a, b);
    u -= t * v; swap(u, v);
  }
  assert(b == 1);
  if (u < 0) u += md;
  return u;
}

int main() {
  int n, alpha;
  scanf("%d %d", &n, &alpha);
  vector<int> ans(n + 1);
  vector<int> strict(n + 1);
  int res = 0;
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 1) {
      ans[i] = mul(power(alpha, (i + 1) / 2), i);
    } else {
      ans[i] = mul(power(alpha, i / 2), i / 2);
      add(ans[i], mul(power(alpha, i / 2 + 1), i / 2));
    }
    strict[i] = ans[i];
    for (int j = 1; j * j <= i; j++) {
      if (i % j == 0 && j < i) {
        sub(ans[i], mul(strict[j], i / j - 1));
        sub(strict[i], mul(strict[j], i / j));
        if (j * j < i && j != 1) {
          j = i / j;
          sub(ans[i], mul(strict[j], i / j - 1));
          sub(strict[i], mul(strict[j], i / j));
          j = i / j;
        }
      }
    }
    res = (res + ans[i]) % md;
  }
  printf("%d\n", res);
  return 0;
}

