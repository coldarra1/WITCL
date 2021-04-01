#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int mod = 1e9 + 7;
int mul(LL a, int b) {
  a *= b;
  return a >= mod ? a % mod : a;
}
int mpow(int a, int b) {
  int ret = 1;
  while (b) {
    if (b & 1) {
      ret = mul(ret, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return ret;
}
int inv(int a) {
  return mpow(a, mod - 2);
}
int prob(int ni, int mi) {
  if (ni == 1) {
    return 1;
  }
  if (mi == 0) {
    return 0;
  }
  return inv(ni - 1);
}
int main() {
  int ans = 1, t;
  cin >> t;
  while (t--) {
    int ni, mi;
    cin >> ni >> mi;
    ans = mul(ans, prob(ni, mi));
    printf("%d\n", ans);
  }
}
