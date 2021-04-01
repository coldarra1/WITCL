#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2048;
constexpr int mod = 1e9 + 7;
constexpr int MOD = 1e9 + 7;
typedef long long LL;
typedef long long ll;
inline int add(int a, int b) {
  a += b;
  return a >= mod ? a - mod : a;
}
inline int sub(int a, int b) {
  a -= b;
  return a < 0 ? a + mod : a;
}
inline int mul(LL a, int b) {
  a *= b;
  return a >= mod ? a % mod : a;
}
inline int mpow(int a, int b) {
  int r = 1;
  while (b) {
    if (b & 1) {
      r = mul(r, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return r;
}
inline int inv(int x) {
  return mpow(x, mod - 2);
}

LL n , m, ik;
constexpr int MAX_N = 1024;
ll dp[MAX_N<<1];

inline void pre_dp() {
  LL bdr = min(n + n , m);
  dp[0] = 1;
  for(ll i = 1; i <= bdr; i++) {
    dp[i] = 0LL;
    for (int j = 1 ; j <= n; ++j) {
      if (i - j < 0 ) break;
      dp[i] = (dp[i] + dp[i - j] * ik % MOD) % MOD;
    }
  }
}
inline vector<ll> mul(vector<ll>& v1 , vector<ll>& v2) {
  int sz1 = (int)v1.size();
  int sz2 = (int)v2.size();
  vector<ll> _v(n + n);
  for(int i = 0; i < n + n; i++) _v[i] = 0;
  // expand
  for(int i = 0; i < sz1; i++) {
    for(int j = 0; j < sz2; j++) {
      (_v[i + j + 1] += v1[i] * v2[j] % MOD) %= MOD;
    }
  }
  // shrink
  for(int i = 0; i < n; i++) {
    for(int j = 1; j <= n; j++) {
      (_v[i + j] += _v[i] * ik) %= MOD;
    }
  }
  for(int i = 0; i < n; i++) _v[i] = _v[i + n];
  _v.resize(n);
  return _v;
}
vector<ll> I , A;
inline ll solve() {
  pre_dp();
  if(m <= n + n) return dp[m];
  I.resize(n);
  A.resize(n);
  for(int i = 0; i < n; i++) {
    I[i] = ik;
    A[i] = ik;
  }
  // dp[m] = /Sum_{i=0}^{n-1} A_i * dp[m - i - 1]
  ll dlt = (m - n) / n;
  ll rdlt = dlt * n;
  while(dlt) {
    if(dlt & 1LL) I = mul(I , A);
    A = mul(A , A);
    dlt >>= 1LL;
  }
  ll ans = 0;
  for(int i = 0; i < n; i++) {
    (ans += I[i] * dp[m - i - 1 - rdlt] % MOD) %= MOD;
  }
  return ans;
}

int main() {
  LL n_, k_;
  int t; cin >> t; while (t--) {
    cin >> k_ >> n_;
    n = k_;
    m = n_;
    ik = inv(k_);
    ll ans;
    if (n_ == -1) {
      ans = mul(2, inv(k_ + 1));
    } else {
      ans = solve();
    }
    printf("%lld\n", ans);
  }
}
