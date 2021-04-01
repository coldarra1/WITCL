#include <bits/stdc++.h>

class MinCostFlow {
public:
  struct Result {
    int flow, cost;
  };

  MinCostFlow(int n, int m = 0) : visited(n), head(n, -1), dist(n), prev(n) {
    edges.reserve(m << 1);
  }

  void add_edge(int u, int v, int capacity, int cost) {
    internal_add_edge(u, v, capacity, cost);
    internal_add_edge(v, u, 0, -cost);
  }

  Result augment(int src, int dst) {
    const int infdist = std::numeric_limits<int>::max();
    std::fill(dist.begin(), dist.end(), infdist);
    dist[src] = 0;
    std::queue<int> queue;
    queue.push(src);
    while (!queue.empty()) {
      int u = queue.front();
      queue.pop();
      visited[u] = false;
      for (int iter = head[u]; ~iter;) {
        auto &e = edges[iter];
        int v = e.v;
        if (e.rest && dist[u] + e.cost < dist[v]) {
          dist[v] = dist[u] + e.cost;
          prev[v] = iter;
          if (!visited[v]) {
            visited[v] = true;
            queue.push(v);
          }
        }
        iter = e.next;
      }
    }
    if (dist[dst] == infdist) {
      return Result{0, 0};
    }
    for (int v = dst; v != src; v = edges[prev[v] ^ 1].v) {
      edges[prev[v]].rest--;
      edges[prev[v] ^ 1].rest++;
    }
    return Result{1, dist[dst]};
  }

private:
  struct Edge {
    int v, next, rest, cost;
  };

  void internal_add_edge(int u, int v, int capacity, int cost) {
    edges.push_back(Edge{v, head[u], capacity, cost});
    head[u] = edges.size() - 1;
  }

  std::vector<bool> visited;
  std::vector<int> head, dist, prev;
  std::vector<Edge> edges;
};

template <typename T> T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }

#ifndef NO_MAIN
int main() {
  // freopen("input", "r", stdin);
  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    MinCostFlow net(n, m);
    for (int i = 0, a, b, c; i < m; ++i) {
      scanf("%d%d%d", &a, &b, &c);
      net.add_edge(a - 1, b - 1, 1, c);
    }
    std::vector<int> ch(1);
    int cost = 0;
    while (true) {
      auto result = net.augment(0, n - 1);
      if (!result.flow) {
        break;
      }
      ch.push_back(cost += result.cost);
    }
    int q;
    scanf("%d", &q);
    while (q--) {
      int u, v;
      scanf("%d%d", &u, &v);
      if (u == 0) {
        puts("NaN");
      } else {
        int x = (v + u - 1) / u;
        if (x >= static_cast<int>(ch.size())) {
          puts("NaN");
        } else {
          int delta = ch[x] - ch[x - 1]; // <= m * C
          auto a = 1LL * ch[x] * u - delta * (1LL * x * u - v);
          auto g = gcd(a, 1LL * v);
          printf("%lld/%lld\n", a / g, v / g);
        }
      }
    }
  }
}
#endif
