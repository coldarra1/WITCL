#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main(void) {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    int best = 1e9, cnt = 0;
    for (int i = 0; i < n; ++i) {
      int a, d;
      scanf("%d%d", &a, &d);
      int t = ((100 + a - 1) / a - 1) * d;
      if (t < best) {
        best = t;
        cnt = 1;
      } else if (t == best) {
        ++cnt;
      }
    }
    double p = 1 - 0.5 * cnt / n;
    printf("%.20lf\n", p);
  }
  return 0;
}
