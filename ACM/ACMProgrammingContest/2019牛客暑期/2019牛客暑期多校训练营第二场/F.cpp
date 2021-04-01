#include <bits/stdc++.h>
using namespace std;
constexpr int N = 18;
typedef long long LL;
int n, all;
LL v[N + N][N + N], ans;
void go(int msk, int got, int pre, LL cst) {
  if (got + got == n) {
    ans = max(ans, cst);
    return;
  }
  if (n - pre - 1 + got < n / 2) {
    return;
  }
  for (int nxt = pre + 1; nxt < n; ++ nxt) {
    LL nxt_cst = cst;
    for (int i = 0; i < n; ++i) {
      if ((msk >> i) & 1)
        nxt_cst -= v[nxt][i];
      else
        nxt_cst += v[nxt][i];
    }
    go(msk | (1 << nxt), got + 1, nxt, nxt_cst);
  }
}
int main() {
  cin >> n;
  n <<= 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> v[i][j];
    }
  }
  all = (1 << n) - 1;
  LL cst = 0;
  for (int i = 0; i < n; ++i) {
    cst += v[0][i];
  }
  go((1 << 0), 1, 0, cst);
  printf("%lld\n", ans);
}
