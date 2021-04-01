// f(i,j) = min(f(k,l)+i-k)+1 for 0<=k<i,0<=l<j
// g(i,j) = min(f(k,l)-k) for 0<=k<i,0<=l<j

#include <bits/stdc++.h>
using namespace std;

const int N = 2E3 + 100, INF = 1E9;
int a[N], b[N * 2];
typedef pair<int, int> P;
pair<P, P> f[N][N * 2], g[N][N * 2];

#define mp make_pair

struct Query {
  int l, r;
  vector<int> rep;
  bool operator<(const Query& other) const {
    return l < other.l || (l == other.l && r < other.r);
  }
};

vector<int> construct_from_queries(vector<int> a, int n, int q) {
  string line;
  char token;
  vector<int> swap;
  vector<Query> query;
  for (int i = 0; i < q; ++i) {
    do {
      getline(cin, line);
    } while (line == "");
    stringstream sstr;
    sstr.str(line);
    sstr >> token;
    if (token == 'R') {
      int l, r, val;
      sstr >> l >> r;
      swap.clear();
      while (sstr >> val) {
        swap.push_back(val);
      }
      query.push_back({l - 1, r, swap});
    } else if (token == 'A') {
      int l, val;
      sstr >> l;
      swap.clear();
      while (sstr >> val) {
        swap.push_back(val);
      }
      query.push_back({l - 1, l - 1, swap});
    } else if (token == 'D') {
      int l, r;
      sstr >> l >> r;
      query.push_back({l - 1, r, vector<int>()});
    } else {
      assert(0);
    }
  }
  vector<int> b;
  for (int i = 0, j = 0; i < (int)a.size() || j < (int)query.size(); ++j) {
    if (j == (int)query.size()) {
      while (i < (int)a.size()) {
        b.push_back(a[i++]);
      }
    } else {
      while (i < query[j].l) {
        b.push_back(a[i++]);
      }
      b.insert(b.end(), query[j].rep.begin(), query[j].rep.end());
      i = query[j].r;
    }
  }
  return b;
}

void solve() {
  int n, m, q;
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  vector<int> aa(a + 1, a + n + 1);
  auto bb = construct_from_queries(aa, n, q);
  m = bb.size();
  for (int i = 1; i <= m; ++i) {
    b[i] = bb[i - 1];
    // cout << b[i] << " ";
  }
  for (int i = 1; i <= n; ++i) {
    f[i][0] = mp(mp(INF, INF), mp(0, 0));
  }
  for (int i = 1; i <= m; ++i) {
    f[0][i] = mp(mp(INF, INF), mp(0, 0));
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      const auto& gg = g[i - 1][j - 1];
      auto& ff = f[i][j];
      ff = {mp(gg.first.first + i, gg.first.second + 1), gg.second};
      if (a[i] == b[j]) {
        ff = min(ff, {f[i - 1][j - 1].first, mp(i - 1, j - 1)});
      }
      // printf("%d %d %d %d %d %d\n", i, j, ff.first.first, ff.first.second,
      //        ff.second.first, ff.second.second);
      g[i][j] = min(min(g[i - 1][j], g[i][j - 1]),
                    {mp(ff.first.first - i, ff.first.second), mp(i, j)});
      // printf("gg %d %d %d %d %d %d\n", i, j, g[i][j].first.first,
      //        g[i][j].first.second, g[i][j].second.first,
      //        g[i][j].second.second);
    }
  }
  cout << f[n][m].first.first << " " << f[n][m].first.second << endl;
  P p = {n, m};
  while (p != mp(0, 0)) {
    int x = p.first, y = p.second;
    P next = f[x][y].second;
    if (f[x][y].first != f[next.first][next.second].first) {
      cout << next.first + 1 << " " << x;
      for (int i = next.second + 1; i <= y; ++i) {
        cout << " " << b[i];
      }
      cout << endl;
    }
    p = next;
  }
}

int main() {
  int q;
  cin >> q;
  while (q--) {
    solve();
  }
}