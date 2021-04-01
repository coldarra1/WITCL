#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr, __VA_ARGS__)

struct Point {
  int x, y, a, b;

  int offset() const { return b - a; }
};

bool operator<(const Point &a, const Point &b) {
  if (a.x != b.x) {
    return a.x < b.x;
  }
  return a.y < b.y;
}

struct SegTree {
  SegTree(int n) : n(n), tree(2 * n) {}

  void add(int l, int r, int k, int c) {
    if (r < k) {
      return;
    }
    int id = get_id(l, r);
    if (k <= l) {
      tree[id].delta += c;
      tree[id].maximum += c;
    } else {
      int m = l + r >> 1;
      add(l, m, k, c);
      add(m + 1, r, k, c);
      tree[id].maximum =
          std::max(tree[get_id(l, m)].maximum, tree[get_id(m + 1, r)].maximum) +
          tree[id].delta;
    }
  }

  long long ask(int l, int r, int k) {
    if (k < l) {
      return -INF;
    }
    int id = get_id(l, r);
    if (r <= k) {
      return tree[id].maximum;
    }
    int m = l + r >> 1;
    return std::max(ask(l, m, k), ask(m + 1, r, k)) + tree[id].delta;
  }

  void insert(int l, int r, int k, long long v) {
    if (k < l || r < k) {
      return;
    }
    int id = get_id(l, r);
    if (l == r) {
      if (tree[id].maximum < v) {
        tree[id].delta = tree[id].maximum = v;
      }
    } else {
      v -= tree[id].delta;
      int m = l + r >> 1;
      insert(l, m, k, v);
      insert(m + 1, r, k, v);
      tree[id].maximum =
          std::max(tree[get_id(l, m)].maximum, tree[get_id(m + 1, r)].maximum) +
          tree[id].delta;
    }
  }

  static inline int get_id(int l, int r) { return l + r | l != r; }

  static const long long INF = 2e14;

  struct Info {
    long long delta, maximum;
  };

  int n;
  std::vector<Info> tree;
};

int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    std::vector<Point> points(n);
    long long sum = 0;
    std::vector<int> y_values;
    y_values.push_back(0);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d%d", &points[i].x, &points[i].y, &points[i].a, &points[i].b);
      y_values.push_back(points[i].y);
      sum += points[i].a;
    }
    std::sort(y_values.begin(), y_values.end());
    y_values.erase(std::unique(y_values.begin(), y_values.end()),
                   y_values.end());
    std::sort(points.begin(), points.end());
    SegTree sgt{n + 1};
    std::vector<long long> dp(n);
    std::vector<int> y(n);
    for (int i = 0; i < n; ++i) {
      y[i] = std::lower_bound(y_values.begin(), y_values.end(), points[i].y) -
             y_values.begin();
    }
    for (int i = 0; i < n;) {
      int j = i;
      long long ww = 0;
      while (j < n && points[i].x == points[j].x) {
        ww += points[j].offset();
        dp[j] = sgt.ask(0, n, y[j] - 1) + ww;
        j++;
      }
      for (int k = i; k < j; ++k) {
        sgt.add(0, n, y[k], points[k].offset());
        sgt.insert(0, n, y[k], dp[k]);
      }
      i = j;
    }
    std::cout << sum + sgt.ask(0, n, n) << std::endl;
  }
}
