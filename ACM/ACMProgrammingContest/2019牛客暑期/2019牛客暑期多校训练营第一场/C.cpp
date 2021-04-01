#include <bits/stdc++.h>

int main()
{
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<int> a(n);
    long long s2 = 0;
    for (int i = 0; i < n; ++ i) {
      scanf("%d", &a[i]);
      s2 += 1LL * a[i] * a[i];
    }
    std::sort(a.begin(), a.end(), std::greater<int>());
    int s1 = 0;
    std::pair<long long, long long> ans(0, 1);
    for (int i = 0; i < n; ++ i) {
      s1 += a[i];
      s2 -= 1LL * a[i] * a[i];
      if (i + 1 == n || (s1 - m) >= (i + 1LL) * a[i + 1]) {
        auto tmp = std::make_pair(1LL * (s1 - m) * (s1 - m) + (i + 1LL) * s2, i + 1);
        if (tmp.first * ans.second > ans.first * tmp.second) {
          ans = tmp;
        }
      }
    }
    ans.second *= 1LL * m * m;
    auto g = std::__gcd(ans.first, ans.second);
    if (ans.first % ans.second == 0) {
      printf("%lld\n", ans.first / ans.second);
    } else {
      printf("%lld/%lld\n", ans.first / g, ans.second / g);
    }
  }
}
