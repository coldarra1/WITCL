#include <bits/stdc++.h>

const int N = 50;
const int M = 100;
const int MOD = 1e9 + 7;

int inverse(int a) {
  return a == 1 ? 1
                : static_cast<uint64_t>(MOD - MOD / a) * inverse(MOD % a) % MOD;
}

template<int V>
int tutte(int n, const std::vector<std::pair<int, int>> &edges, int seed) {
  static int mat[V][V];
  memset(mat, 0, sizeof(mat));
  std::mt19937 gen(seed);
  std::uniform_int_distribution<int> dist(1, MOD - 1);
  for (auto &&e : edges) {
    auto x = dist(gen);
    mat[e.first][e.second] = x;
    mat[e.second][e.first] = MOD - x;
  }
  int rank = 0;
  for (int j = 0; j < n; ++j) {
    int pivot = rank;
    while (pivot < n && !mat[pivot][j]) {
      pivot++;
    }
    if (pivot < n) {
      for (int k = 0; k < n; ++k) {
        std::swap(mat[rank][k], mat[pivot][k]);
      }
      const uint64_t inv = inverse(mat[rank][j]);
      for (int i = rank + 1; i < n; ++i) {
        if (mat[i][j]) {
          const uint64_t tmp = inv * mat[i][j] % MOD;
          for (int k = j; k < n; ++k) {
            mat[i][k] += MOD - tmp * mat[rank][k] % MOD;
            if (mat[i][k] >= MOD) {
              mat[i][k] -= MOD;
            }
          }
        }
      }
      rank++;
    }
  }
  return rank;
}

#ifndef NO_MAIN

int deg[N];

int main() {
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    int demand = 0;
    for (int i = 0; i < n; ++i) {
      scanf("%d", deg + i);
      demand += deg[i];
    }
    std::vector<std::pair<int, int>> edges;
    for (int i = 0, a, b; i < m; ++i) {
      scanf("%d%d", &a, &b);
      a--, b--;
      if (deg[a] == 2) {
        std::swap(a, b);
      }
      if (deg[a] == 2) {
        edges.emplace_back(a << 1 | 0, n + i << 1 | 0);
        edges.emplace_back(a << 1 | 1, n + i << 1 | 0);
        edges.emplace_back(b << 1 | 0, n + i << 1 | 1);
        edges.emplace_back(b << 1 | 1, n + i << 1 | 1);
        edges.emplace_back(n + i << 1 | 0, n + i << 1 | 1);
        demand += 2;
      } else if (deg[b] == 2) {
        edges.emplace_back(a << 1, b << 1 | 0);
        edges.emplace_back(a << 1, b << 1 | 1);
      } else {
        edges.emplace_back(a << 1, b << 1);
      }
    }
    puts(tutte<(N + M) << 1>(n + m << 1, edges, 0) == demand ? "Yes" : "No");
  }
}
#endif
