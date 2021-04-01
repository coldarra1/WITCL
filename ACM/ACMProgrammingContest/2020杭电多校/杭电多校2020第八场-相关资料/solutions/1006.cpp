#include <bits/stdc++.h>
using namespace std;

const int N = 1E5 + 100;
int l[N], r[N];

int main() {
  ios::sync_with_stdio(false);
  int q;
  cin >> q;
  while (q--) {
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
      cin >> l[i] >> r[i];
    }
    for (int i = 1; i < n; ++i) {
      l[i + 1] = max(l[i + 1], l[i] - k);
      r[i + 1] = min(r[i + 1], r[i] + k);
    }
    for (int i = n; i > 1; --i) {
      l[i - 1] = max(l[i - 1], l[i] - k);
      r[i - 1] = min(r[i - 1], r[i] + k);
    }
    bool ok = true;
    for (int i = 1; i <= n; ++i) {
      if (l[i] > r[i]) {
        ok = false;
      }
    }
    if (ok) {
      cout << "YES" << endl;
      for (int i = 1; i <= n; ++i) {
        cout << l[i];
        if (i < n) {
          cout << " ";
        } else {
          cout << endl;
        }
      }
    } else {
      cout << "NO" << endl;
    }
  }
}