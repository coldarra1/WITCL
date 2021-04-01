#include <bits/stdc++.h>

static const int MOD = 1e9 + 7;

void update(int &x, int a) {
  x += a;
  if (x >= MOD) {
    x -= MOD;
  }
}

int main() {
  int a, b;
  while (scanf("%d%d", &a, &b) == 2) {
    int s = a + b;
    std::array<std::vector<int>, 2> dp{std::vector<int>(s + 1),
                                       std::vector<int>(s + 1)};
    dp[0][0] = 1;
    for (int i = 0; i <= s; ++i) {
      std::fill(dp[i + 1 & 1].begin(), dp[i + 1 & 1].end(), 0);
      for (int j = 0; j <= s; ++j) {
        int cnt_a = 0;
        int cnt_b = 0;
        {
          int xy = std::max(a - i, 0);
          int y = std::min(i, a) - std::max(j - b, 0);
          if (y < 0) {
            continue;
          }
          cnt_a += xy;
          cnt_b += y;
        }
        {
          int xy = std::max(b - j, 0);
          int y = std::min(j, b) - std::max(i - a, 0);
          if (y < 0) {
            continue;
          }
          cnt_b += xy;
          cnt_a += y;
        }
        if (cnt_a > 0) {
          update(dp[i + 1 & 1][j], dp[i & 1][j]);
        }
        if (cnt_b > 0) {
          update(dp[i & 1][j + 1], dp[i & 1][j]);
        }
      }
    }
    printf("%d\n", dp[s & 1][s]);
  }
}
