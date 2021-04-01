#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 1e5;
const int maxv = maxn * 2 + 2;

typedef long long li;
typedef pair<int, int> pii;
const li infl = ~0LLU >> 2;

int n, m, s, t, cost_change;
char type[maxn + 1];
vector<pii> g[maxv];
int nv, S, T;
li dist[maxv];

struct Node {
  int u;
  li d;
  bool operator < (const Node &b) const {
    return d > b.d;
  }
};

priority_queue<Node> que;

li Dijkstra(void) {
  fill(dist, dist + nv, infl);
  dist[S] = 0;
  que.push({S, 0});
  while (!que.empty()) {
    int u = que.top().u;
    li d = que.top().d;
    que.pop();
    if (d != dist[u]) continue;
    for (pii e : g[u]) {
      int v = e.first, len = e.second;
      if (dist[u] + len < dist[v]) {
        dist[v] = dist[u] + len;
        que.push({v, dist[v]});
      }
    }
  }
  return dist[T];
}

inline bool Conflict(int t, char c) {
  return (t == 0 && c == 'R') || (t == 1 && c == 'L');
}

inline void AddEdge(int u, int v, int len) {
  g[u].push_back({v, len});
  g[v].push_back({u, len});
}

void Solve(void) {
  scanf("%d%d%d%d%d", &n, &m, &s, &t, &cost_change);
  --s; --t;
  scanf("%s", type);

  nv = n * 2 + 2;
  for (int i = 0; i < nv; ++i) {
    g[i].clear();
  }

  for (int i = 0; i < m; ++i) {
    int a, b, d;
    scanf("%d%d%d", &a, &b, &d);
    --a; --b;
    for (int ta = 0; ta <= 1; ++ta) {
      if (Conflict(ta, type[a])) continue;
      for (int tb = 0; tb <= 1; ++tb) {
        if (Conflict(tb, type[b])) continue;
        AddEdge(a << 1 | ta, b << 1 | tb, d + (ta != tb) * cost_change);
      }
    }
  }

  S = n * 2, T = S + 1;
  for (int ts = 0; ts <= 1; ++ts) {
    if (Conflict(ts, type[s])) continue;
    AddEdge(S, s << 1 | ts, 0);
  }
  for (int tt = 0; tt <= 1; ++tt) {
    if (Conflict(tt, type[t])) continue;
    AddEdge(T, t << 1 | tt, 0);
  }

  li ans = Dijkstra();
  printf("%lld\n", ans);
}

int main(void) {
  int T;
  scanf("%d", &T);
  while (T--) {
    Solve();
  }
  return 0;
}
