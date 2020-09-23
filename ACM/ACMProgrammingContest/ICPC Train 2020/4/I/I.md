## Ideal Pyramid

​	因为四棱柱的角度是确定的，所以对于某个高点$(x, y, h)$来说，要使四棱柱把它包括其中，它的最小占地面积是固定的。所以可以预先计算出所有高点的“必须占地面积”。则题目可以降维到：求平面上包括$n$个正方形的最小正方形。求出该正方形后，就可以反过来求中点和高度$h$了。

​	又因为角度都是45°，所以高度$h$在地面的投影也是$h$。所以设所求正方形的四条边分别是$xl, xr, yl, yr$，则显然满足：
$$
\begin{aligned}xl = &\min( x_i - h_i ) \\xr = &\max( x_i + h_i ) \\yl = &\min( y_i - h_i ) \\yr = &\max( y_i + h_i )\end{aligned}
$$
的正方形就是所求答案。

$Solution:$

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 4e18;

int main() {
  int n;
  cin >> n;
  vector<ll> x(n), y(n), h(n);
  for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> h[i];

  ll min_x = INF, max_x = -INF, min_y = INF, max_y = -INF;
  for (int i = 0; i < n; i++) {
    min_x = min(min_x, x[i] - h[i]);
    max_x = max(max_x, x[i] + h[i]);
    min_y = min(min_y, y[i] - h[i]);
    max_y = max(max_y, y[i] + h[i]);
  }
  ll rx = (min_x + max_x) / 2, ry = (min_y + max_y) / 2;
  ll rh = (max(max_x - min_x, max_y - min_y) + 1) / 2;
  cout << rx << " " << ry << " " << rh << endl;
}
```

