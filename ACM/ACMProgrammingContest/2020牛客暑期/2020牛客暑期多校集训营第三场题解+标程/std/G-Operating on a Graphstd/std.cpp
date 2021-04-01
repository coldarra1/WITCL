#include <cmath>
#include <functional>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <chrono>
#include <cstring>

using namespace std;

typedef long long ll;

#ifdef iq
  mt19937 rnd(228);
#else
  mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
#endif

const int N = 1e6;

struct head {
  head *r;
  int val;
  head(int x): r(0), val(x) {
  }
};

int dsu[N];

int get(int v) {
  if (v == dsu[v]) return v;
  else return dsu[v] = get(dsu[v]);
}

pair <head*, head*> g[N];

pair <head *, head *> merge(pair <head *, head *> a, pair <head *, head *> b) {
  if (!a.second) return b;
  else {
    a.second->r = b.first;
    return {a.first, b.second};
  }
}

pair <head*, head*> lst(int x) {
  head *t = new head(x);
  return {t, t};
}

int main() {
#ifdef iq
  freopen("a.in", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      dsu[i] = i;
      g[i] = {0, 0};
    }
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      g[x] = merge(g[x], lst(y));
      g[y] = merge(g[y], lst(x));
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
      int c;
      cin >> c;
      if (get(c) != c) {
        continue;
      } else {
        vector <int> ord;
        for (head *s = g[c].first; s != 0; s = s->r) {
          int z = s->val;
          if (get(z) != c) {
            int who = get(z);
            dsu[who] = c;
            ord.push_back(who);
          }
        }
        g[c] = {0, 0};
        for (int p : ord) {
          g[c] = merge(g[c], g[p]);
        }
      }
    }
    for (int i = 0; i < n; i++) cout << get(i) << ' ';
    cout << '\n';
  }
}