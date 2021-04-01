#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct Point {
  int x;
  int y;
};

struct Edge {
  ll dis;
  int a;
  int b;
  bool operator<(const Edge& rhs) const {
    return dis > rhs.dis;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<Point> P(n + 1);
    for (int i = 1; i <= n; i++) {
      cin >> P[i].x >> P[i].y;
    }
    vector<Edge> E;
    for (int i = 1; i <= n; i++) {
      for (int j = i + 1; j <= n; j++) {
        auto get_dis = [&](int x1, int y1, int x2, int y2) -> ll {
          return 1LL * (x1 - x2) * (x1 - x2) + 1LL * (y1 - y2) * (y1 - y2);
        };
        E.push_back({get_dis(P[i].x, P[i].y, P[j].x, P[j].y), i, j});
      }
    }
    sort(E.begin(), E.end());
    vector<int> del(n + 1);
    int m = (int)E.size();
    vector<int> t;
    ll td = -1;
    for (int i = 0; i < m; i++) {
      if (del[E[i].a] || del[E[i].b]) continue;
      if (td == -1 || td == E[i].dis) {
        t.push_back(E[i].a);
        t.push_back(E[i].b);
        td = E[i].dis;
      } else {
        for (auto e: t) del[e] = 1;
        if (del[E[i].a] || del[E[i].b]) {
          td = -1;
          t.clear();
          continue;
        }
        td = E[i].dis;
        t = {E[i].a, E[i].b};
      }
    }
    if (td != -1) {
      for (auto e: t) del[e] = 1;
    }
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
      if (!del[i]) ans.push_back(i);
    }
    assert((int)ans.size() <= 1);
    if (ans.empty()) {
      cout << "YES\n";
    } else if (ans[0] != 1) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }
  return 0;
}
