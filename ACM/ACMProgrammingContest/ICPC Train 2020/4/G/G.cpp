#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;

using ll = long long;

// min x : y0 <= (a * x) % m <= y1
pair<ll, ll> solve(ll a, ll m, ll y0, ll y1) {
  if (y1 <= y0) return {0, 0};
  if (a > m) {
    return solve(a % m, m, y0, y1);
  }
  if (2 * a > m) {
    auto res = solve((m - a) % m, m, (m - y1) % m, (m - y0) % m);
    res.second = (m - res.second) % m;
    return res;
  }
  if (a == 0) return {-1, -1};
  ll mv = (y0 + a - 1) / a * a;
  if (mv <= y1) return {mv / a, mv};
  if (m % a == 0) return {-1, -1};

  auto [steps, shift] = solve(a - (m % a), a, y0 % a, y1 % a);
  if (steps == -1) return {-1, -1};
  assert((steps * m + shift) % a == 0);
  ll big_steps = (steps * m + shift) / a;
  ll small_steps = (y0 - shift + a - 1) / a;
  shift += small_steps * a;
  assert(y0 <= shift && shift <= y1);
  return {(big_steps + small_steps) % m, shift};
}

int norm(ll x, int m) {
  return (x % m + m) % m;
};


int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif
  int n, w, h;
  while (scanf("%d%d%d",&w, &h, &n) == 3) {
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &x[i], &y[i]);
    }
    x.push_back(x[0]);
    y.push_back(y[0]);

    vector<pair<int, pair<int, int>>> xs;
    vector<pair<int, pair<int, int>>> ys;
    
    w *= 2;
    h *= 2;

    for (int i = 0; i < n; i++) {
      if (x[i] == x[i + 1]) {
        xs.push_back({x[i], {y[i], y[i + 1]}});
        xs.push_back({w - x[i], {y[i], y[i + 1]}});
        xs.push_back({x[i], {h - y[i + 1], h - y[i]}});
        xs.push_back({w - x[i], {h - y[i + 1], h - y[i]}});
      } else {
        ys.push_back({y[i], {x[i], x[i + 1]}});
        ys.push_back({h - y[i], {x[i], x[i + 1]}});
        ys.push_back({y[i], {w - x[i + 1], w - x[i]}});
        ys.push_back({h - y[i], {w - x[i + 1], w - x[i]}});
      }
    }

    for (auto &[x, p] : xs) {
      if (p.first > p.second) {
        swap(p.first, p.second);
      }
    }
    for (auto &[x, p] : ys) {
      if (p.first > p.second) {
        swap(p.first, p.second);
      }
    }


    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
      ll x, y;
      scanf("%lld%lld", &x, &y);
      ll t = -1;
      for (int it = 0; it < 2; it++) {
        for (const auto &[sx, p] : xs) {
           int first = norm(sx - x, w);
           int ny = norm(y + first, h);
           int lb = norm(p.first - ny, h);
           int rb = norm(p.second - ny, h);
           auto res = solve(w, h, lb, rb);
           if (res.first != -1) {
             ll ans = res.first * 1LL * w + first;
             if (t == -1 || t > ans) {
               t = ans;
             }
           }
        }
        xs.swap(ys);
        swap(w, h);
        swap(x, y);
      }
      if (t == -1) {
        printf("-1\n");
      } else {
        x = norm(x + t, w);
        y = norm(y + t, h);
        printf("%lld %lld %lld\n", t, min(x, w - x), min(y, h - y));
      }
    }
  }
}

