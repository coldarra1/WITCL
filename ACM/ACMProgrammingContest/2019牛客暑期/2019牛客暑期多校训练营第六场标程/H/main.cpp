#include <bits/stdc++.h>

inline int read(int &x) {
  int c;
  while (!isdigit(c = getchar()));
  x = c - '0';
  while (isdigit(c = getchar())) {
    x = x * 10 + c - '0';
  }
}

using LL = long long;

const int inf = 0x3f3f3f3f;

const int max_N = (int)1e5 + 21;
const int max_K = 21;

int n, m, A[max_K], B[max_K];

int dis1[max_K][max_N], dis2[max_K][max_N];

std::vector<int> vec[max_N];

void bfs1(int u, int *dis) {
  static int Q[max_N], tot;
  for (int i = 1; i <= n; ++i) {
    dis[i] = -1;
  }
  Q[tot = 1] = u;
  dis[u] = 0;
  for (int i = 1; i <= tot; ++i) {
    u = Q[i];
    for (auto &v : vec[u]) {
      if (dis[v] == -1) {
        dis[v] = dis[u] + 1;
        Q[++tot] = v;
      }
    }
  }
}

LL bfs2(const int *dis1, const int *dis2) {
  static int Q1[max_N], Q2[max_N];
  static int dis[max_N], cnt[max_N * 2];
  static bool vis[max_N];
  for (int i = 0; i <= 2 * n; ++i) {
    cnt[i] = 0;
  }
  for (int i = 1; i <= n; ++i) {
    assert(dis1[i] != -1);
    assert(dis2[i] != -1);
    dis[i] = dis1[i] + dis2[i];
    ++cnt[dis[i]];
    vis[i] = false;
  }
  for (int i = 1; i <= 2 * n; ++i) {
    cnt[i] += cnt[i - 1];
  }
  int h1 = 1, tot1 = cnt[2 * n];
  for (int i = n; i; --i) {
    Q1[cnt[dis[i]]--] = i;
  }
  int h2 = 1, tot2 = 0;
  while (h1 <= tot1 || h2 <= tot2) {
    int u;
    if (h2 > tot2 || (h1 <= tot1 && dis1[Q1[h1]] + dis2[Q1[h1]] < dis[Q2[h2]])) {
      u = Q1[h1++];
    } else {
      u = Q2[h2++];
    }
    if (vis[u])
      continue;
    vis[u] = true;
    for (auto &v : vec[u]) {
      if (dis[v] > dis[u] + 1) {
        dis[v] = dis[u] + 1;
        Q2[++tot2] = v;
      }
    }
  }
  LL ret = 0;
  for (int i = 1; i <= n; ++i) {
    assert(dis[i] < inf);
    ret += dis[i];
  }
  // printf("%lld\n", ret);
  return ret;
}

void testCase(int id) {
  read(n);
  read(m);
  for (int i = 1, u, v; i <= m; ++i) {
    read(u);
    read(v);
    vec[u].push_back(v);
    vec[v].push_back(u);
  }
  int k1, k2;
  read(k1);
  for (int i = 1; i <= k1; ++i) {
    read(A[i]);
    bfs1(A[i], dis1[i]);
  }
  read(k2);
  for (int i = 1; i <= k2; ++i) {
    read(B[i]);
    bfs1(B[i], dis2[i]);
  }
  LL ans1 = 0;
  for (int i = 1; i <= k1; ++i) {
    for (int j = 1; j <= k2; ++j) {
      // printf("bfs2(%d, %d) = ", A[i], B[j]);
      ans1 += bfs2(dis1[i], dis2[j]);
    }
  }
  LL ans2 = 1LL * k1 * k2 * n;
  LL g = std::__gcd(ans1, ans2);
  ans1 /= g, ans2 /= g;
  if (ans2 == 1) {
    printf("Case #%d: %lld\n", id, ans1);
  } else {
    printf("Case #%d: %lld/%lld\n", id, ans1, ans2);
  }
}

void clr() {
  for (int i = 1; i <= n; ++i) {
    vec[i].clear();
  }
}

int main() {
  int T;
  read(T);
  for (int i = 1; i <= T; ++i) {
    testCase(i);
    clr();
  }
}