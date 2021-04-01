#include <bits/stdc++.h>

struct Height {
  Height(int n, int m, std::vector<std::vector<char>> &g)
      : n(n), m(m), grid(g) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        if (grid[i][j] == '-') {
          grid[i][j + 1] = ' ';
        }
        if (grid[i][j] == '|') {
          grid[i + 1][j] = ' ';
        }
      }
    }
  }

  void compute(int x0, int y0) {
    height =
        std::vector<std::vector<int>>(n + 1, std::vector<int>(m + 1, INT_MAX));
    dfs(x0, y0, 0);
  }

  void dfs(int x, int y, int h) {
    if (height[x][y] == INT_MAX) {
      height[x][y] = h;
      int parity = x + y & 1;
      if (x && (y == 0 || grid[x - 1][y - 1] != '-')) {
        dfs(x - 1, y, h + (parity ? -1 : 1));
      }
      if (x < n && (y == 0 || grid[x][y - 1] != '-')) {
        dfs(x + 1, y, h + (parity ? -1 : 1));
      }
      if (y && (x == 0 || grid[x - 1][y - 1] != '|')) {
        dfs(x, y - 1, h + (parity ? 1 : -1));
      }
      if (y < m && (x == 0 || grid[x - 1][y] != '|')) {
        dfs(x, y + 1, h + (parity ? 1 : -1));
      }
    }
  }

  int n, m;
  std::vector<std::vector<char>> &grid;
  std::vector<std::vector<int>> height;
};

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    std::vector<std::vector<char>> g1(n, std::vector<char>(m + 1));
    auto g2 = g1;
    for (int i = 0; i < n; ++i) {
      scanf("%s", g1[i].data());
    }
    auto h1 = Height(n, m, g1);
    for (int i = 0; i < n; ++i) {
      scanf("%s", g2[i].data());
    }
    auto h2 = Height(n, m, g2);
    int result = -1;
    std::mt19937 gen{0};
    for (int _ = 0; _ < 2; ++_) {
      int x0 = std::uniform_int_distribution<int>(0, n)(gen);
      int y0 = std::uniform_int_distribution<int>(0, m)(gen);
      if (std::uniform_int_distribution<int>(0, 1)(gen)) {
        x0 = std::uniform_int_distribution<int>(0, 1)(gen) * n;
      } else {
        y0 = std::uniform_int_distribution<int>(0, 1)(gen) * m;
      }
      h1.compute(x0, y0);
      h2.compute(x0, y0);
      int tmp = 0;
      for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
          tmp += std::abs(h1.height[i][j] - h2.height[i][j]);
        }
      }
      if (~result) {
        assert(result == tmp);
      }
      result = tmp;
    }
    assert((result & 3) == 0);
    printf("%d\n", result >> 2);
  }
}
