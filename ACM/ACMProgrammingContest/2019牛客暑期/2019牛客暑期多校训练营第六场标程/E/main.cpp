#include <bits/stdc++.h>

using std::min;

const int max_N = (int)2e3 + 21;

bool map[max_N][max_N];

inline void set(int x, int y) { map[x][y] = true; }

#define pos(x) (x)
#define neg(x) (tot + (x))

int edge_id[4][4], tot;

std::vector<int> vec[32];

int f[4] = {2, 3, 1, 0};

// 0 -> 2, 1 -> 3, 2 -> 1, 3 -> 0
// i < j -> G, i > j -> \bar{G}

int dfn[100], low[100], cnt;

int col[100], col_cnt;

int st[100], top;

void dfs(int u) {
  dfn[u] = low[u] = ++cnt;
  st[++top] = u;
  for (auto &v : vec[u]) {
    if (!dfn[v]) {
      dfs(v);
      low[u] = min(low[u], low[v]);
    } else if (!col[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    col[u] = ++col_cnt;
    while (st[top] != u) {
      col[st[top--]] = col_cnt;
    }
    --top;
  }
}

bool init() {
  memset(edge_id, 0, sizeof(edge_id));
  tot = 0;

  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      edge_id[i][j] = ++tot;
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      int u = f[i], v = f[j];
      if (u > v)
        std::swap(u, v);
      vec[pos(edge_id[i][j])].push_back(neg(edge_id[u][v]));
      vec[neg(edge_id[i][j])].push_back(pos(edge_id[u][v]));
    }
  }
  for (int i = 1; i <= tot * 2; ++i) {
    if (dfn[i])
      continue;
    dfs(i);
  }
  for (int i = 1; i <= tot; ++i) {
    if (col[i] == col[i + tot])
      return false;
  }
  return true;
}

void testCase(int id) {
  int n;
  scanf("%d", &n);
  int k = n / 4, m = n % 4;
  if (m > 1) {
    printf("Case #%d: No\n", id);
    return;
  }
  auto get_id = [&k](int x, int y) { return x * k + y + 1; };
  for (int t = 0; t < 2; ++t) {
    for (int i = 0; i < k; ++i) {
      for (int j = i + 1; j < k; ++j) {
        set(get_id(t, i), get_id(t, j));
        set(get_id(t, j), get_id(t, i));
      }
      if (m) {
        set(get_id(t, i), n);
        set(n, get_id(t, i));
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      if (col[neg(edge_id[i][j])] < col[pos(edge_id[i][j])]) {
        for (int a = 0; a < k; ++a) {
          for (int b = 0; b < k; ++b) {
            set(get_id(i, a), get_id(j, b));
            set(get_id(j, b), get_id(i, a));
          }
        }
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    map[i][i] = false;
  }
  printf("Case #%d: Yes\n", id);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
      printf("%c", "01"[map[i][j]]);
    }
    puts("");
  }
  int tot = 0;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < k; ++j) {
      printf("%d%c", get_id(f[i], j), " \n"[++tot == n]);
    }
  }
  if (m) {
    printf("%d\n", n);
  }
}

void clr() { memset(map, 0, sizeof map); }

int main() {
  assert(init());
  /*for (int i = 0; i < 4; ++i) {
    for (int j = i + 1; j < 4; ++j) {
      if (col[pos(edge_id[i][j])] < col[neg(edge_id[i][j])]) {
        printf("%d %d\n", i, j);
      }
    }
  }*/
  int T;
  scanf("%d", &T);
  for (int i = 1; i <= T; ++i) {
    testCase(i);
    clr();
  }
}