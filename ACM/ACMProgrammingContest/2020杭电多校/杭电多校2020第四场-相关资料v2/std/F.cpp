#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

typedef double real;

const int maxn = 5e4;
const int hour_full = 86400 / 2, min_full = hour_full / 12;
const real pi = acos(-1);

int n;
real phour[maxn], pmin[maxn];
typedef pair<real, real> prr;

namespace solver {
  const int maxe = (maxn + 1) * 4;

  int ne, val;
  struct Event {
    real t;
    int d;
    bool operator < (const Event &b) const {
      return t < b.t;
    }
  } ev[maxe];

  void Init(void) {
    ne = val = 0;
  }

  void Add(real l, real r, int w = 1) {
    ev[ne++] = {l, w};
    ev[ne++] = {r, -w};
    if (l > r) val += w;
  }

  vector<prr> Solve(int least) {
    real begin = 0;
    vector<prr> ans;
    sort(ev, ev + ne);
    for (int i = 0; i < ne; ++i) {
      if (ev[i].d > 0) {
        if (val < least && (val + ev[i].d) >= least) {
          begin = ev[i].t;
        }
      } else {
        if (val >= least && (val + ev[i].d) < least) {
          ans.push_back({begin, ev[i].t});
        }
      }
      val += ev[i].d;
    }
    if (val >= least) {
      ans.push_back({begin, 2 * pi});
    }
    return ans;
  }
}

bool Check(real lim) {
  solver::Init();
  for (int i = 0; i < n; ++i) {
    real l = fmod(phour[i] - lim + 2 * pi, 2 * pi),
      r = fmod(phour[i] + lim + 2 * pi, 2 * pi);
    solver::Add(l, r);
  }
  vector<prr> ans_h = solver::Solve(n);
  if (ans_h.empty()) return false;

  solver::Init();
  for (int i = 0; i < n; ++i) {
    real l = fmod(pmin[i] - lim + 2 * pi, 2 * pi),
      r = fmod(pmin[i] + lim + 2 * pi, 2 * pi);
    solver::Add(l, r);
  }
  vector<prr> ans_m = solver::Solve(n);
  if (ans_m.empty()) return false;

  solver::Init();
  for (prr i : ans_m) {
    solver::Add(i.first, i.second, 2 * (n + 1));
  }
  for (prr i : ans_h) {
    real l = i.first, r = i.second;
    if (r - l >= pi / 6) {
      return true;
    }
    solver::Add(fmod(l * 12, 2 * pi), fmod(r * 12, 2 * pi));
  }
  vector<prr> ans = solver::Solve(2 * (n + 1) + 1);
  return ans.size();
}

void Solve(void) {
  real l = 0, r = pi;
  for (int _ = 0; _ < 50; ++_) {
    real mid = (l + r) / 2;
    if (Check(mid)) {
      r = mid;
    } else {
      l = mid;
    }
  }
  printf("%.20lf\n", l / pi * 180);
}

int main(void) {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      int hh, mm, ss;
      scanf("%d:%d:%d", &hh, &mm, &ss);
      ss = (hh * 60 + mm) * 60 + ss;
      phour[i] = (ss % hour_full) / (real)hour_full * (2 * pi);
      pmin[i] = (ss % min_full) / (real)min_full * (2 * pi);
    }
    Solve();
  }
  return 0;
}
