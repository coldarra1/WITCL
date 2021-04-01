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

vector <pair <vector <int>, vector <int> > > ok[7];

int main() {
#ifdef iq
  freopen("a.in", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  for (int m = 4; m <= 6; m++) {
    vector <int> p(m);
    for (int i = 0; i < m; i++) p[i] = i;
    vector <vector <int> > e;
    do {
      bool bad = false;
      for (int i = 0; i < m; i++) {
        if (p[i] == i || p[p[i]] != i) {
          bad = true;
        }
      }
      if (bad) continue;
      e.push_back(p);
    } while (next_permutation(p.begin(), p.end()));
    for (auto c : e) {
      for (auto d : e) {
        if (c < d) {
          bool sad = false;
          for (int i = 0; i < m; i++) {
            if (c[i] == d[i]) sad = true;
          }
          if (sad) continue;
          ok[m].push_back({c, d});
        }
      }
    }
  }
  const ll inf = (ll) (1e18);
  vector <int> z(20);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    auto cost = [&] (int l, int r) {
      for (int i = l; i < r; i++) {
        z[i - l] = a[i];
      }
      ll ret = inf;
      for (auto &c : ok[r - l]) {
        ll sum = 0;
        for (int s = 0; s < r-  l; s++) {
          if (c.first[s] < s) {
            sum += abs(z[c.first[s]] - z[s]);
          }
          if (c.second[s] < s) {
            sum += abs(z[c.second[s]] - z[s]);
          }
        }
        ret = min(ret, sum);
      }
      return ret;
    };
    sort(a.begin(), a.end());
    vector <ll> dp(n + 1, inf);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
      if (i + 3 < n) {
        dp[i + 4] = min(dp[i + 4], dp[i] + cost(i, i + 4));
      }
      if (i + 5 < n) {
        dp[i + 6] = min(dp[i + 6], dp[i] + cost(i, i + 6));
      }
    }
    cout << dp[n] << '\n';
  }
}