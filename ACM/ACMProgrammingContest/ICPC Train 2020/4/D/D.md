## Double Palindrome

​	要计算长度为n的Double Palindrome，可设函数$R(n, k)$为在长度为k的字符集合里构造Double Palindrome的个数。为此，从0~n - 1遍历第一个回文串的长度，由于长度为l的回文串在大小为k的字符集里的数量是$k^{\lceil\frac{l}{2}\rceil}$，所以总和为：$R(n, k) = \sum^{n-1}_{l=0} k^{\lceil\frac{l}{2}\rceil}\cdot k^{\lceil\frac{n-l}{2}\rceil}$。

​	但是，如果按这个式子来算，一些情况就会被计数多次，比如`abacabacabac`。假设字符串s可以被分成两种不同的Double Palindrome，设一种分配的回文长度分别等于$l_1, l_2(l_1 < l_2)$。则：
$$
s_i=s_{l_1-1-i \mod n}= s_{l_2-l_1+i \mod n},
$$
​	即，s是有周期$l_2-l_1$，或者说$\gcd(n, l_2 - l_1)$的。设s的最小正周期为p，并且p为不超过两个回文串的Double Palindrome。则可以计算$D(n,k)$，长度为k的字符集里长度为n的只有一种分配方式的Double Palindrome：
$$
D(n, k) = R(n, k) - \sum\limits_{l|n,\ l<n}\frac{n}{l}D(l, k)
$$
​	则答案为$\sum\limits_n\sum\limits_{l|n}D(l, k)$，时间复杂度为$O(n\log n)$。

$Solution:$

```c++
#include <bits/stdc++.h>

using namespace std;

const int md = 998244353;

inline void add(int &a, int b) {
  a += b;
  if (a >= md) a -= md;
}

inline void sub(int &a, int b) {
  a -= b;
  if (a < 0) a += md;
}

inline int mul(int a, int b) {
  return (int) ((long long) a * b % md);
}

inline int power(int a, long long b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

inline int inv(int a) {
  a %= md;
  if (a < 0) a += md;
  int b = md, u = 0, v = 1;
  while (a) {
    int t = b / a;
    b -= t * a; swap(a, b);
    u -= t * v; swap(u, v);
  }
  assert(b == 1);
  if (u < 0) u += md;
  return u;
}

int main() {
  int n, alpha;
  scanf("%d %d", &n, &alpha);
  vector<int> ans(n + 1);
  vector<int> strict(n + 1);
  int res = 0;
  for (int i = 1; i <= n; i++) {
    if (i % 2 == 1) {
      ans[i] = mul(power(alpha, (i + 1) / 2), i);
    } else {
      ans[i] = mul(power(alpha, i / 2), i / 2);
      add(ans[i], mul(power(alpha, i / 2 + 1), i / 2));
    }
    strict[i] = ans[i];
    for (int j = 1; j * j <= i; j++) {
      if (i % j == 0 && j < i) {
        sub(ans[i], mul(strict[j], i / j - 1));
        sub(strict[i], mul(strict[j], i / j));
        if (j * j < i && j != 1) {
          j = i / j;
          sub(ans[i], mul(strict[j], i / j - 1));
          sub(strict[i], mul(strict[j], i / j));
          j = i / j;
        }
      }
    }
    res = (res + ans[i]) % md;
  }
  printf("%d\n", res);
  return 0;
}
```

