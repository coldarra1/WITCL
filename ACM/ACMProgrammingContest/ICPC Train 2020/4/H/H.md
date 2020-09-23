# 解题报告

## High Load Database

显然当$t<max\{ a_i\}$的时候一定无解，此时直接输出$Impossible$即可。

对于单次询问，存在一种简单的$O(n)$贪心算法，即从$a_1$开始依次遍历每个事务，如果当前事务加入可以加入前一个事务所在的批次，则直接加入即可，否则将该请求作为一个新的批次的左区间端点。如果利用二分算法找每个批次的右区间端点，则可以做到$O(ans*logn )$的复杂度，其中$ans$即本次询问的答案。

考虑如何计算此算法的均摊复杂度。设$A=\sum a_i$。我们将事务分成$t/2 \leq a_i$的大事务和$t/2 > a_i$的小事务。假设大事务有$M(M < 2A/t)$个，则包含大事务和相邻事务的批次不超过$3M=O(A/t)$个。一个仅包含小事务且下一个批次也仅包含小事务的批次中请求一定大于等于$t/2$个（否则可以从下一个批次拿一个事务放到当前批次），这样有小教育组成的块数不超过$O(A/t)$。所以$ans$的规模为$O(A/t)$。如果对答案进行记忆化，则答案和一定小于$O(\sum_{t=1}^{q}A/t)$，即$O(AlogA)$。总复杂度$O(A*logA*logn)$ 。

$Std:$

```c++
#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  int sum = 0;
  int maxCodeBlock = 0;
  for (int i : a) {
      sum += i;
      maxCodeBlock = max(maxCodeBlock, i);
  }
  int q;
  cin >> q;
  vector<int> b = a;
  for (int i = 1; i < n; i++) b[i] += b[i - 1];
  vector<int> answer(sum + 1, -1);
  for (int i = 0; i < q; i++) {
    int k;
    cin >> k;
    if (k < maxCodeBlock) {
        cout << "Impossible\n";
        continue;
    }
    if (answer[k] < 0) {
      int cur = 0;
      int curAns = 0;
      int alreadyHave = 0;
      while (cur < n) {
        int left = cur - 1;
        int right = n;
        while (left < right - 1) {
          int mid = (left + right) >> 1;
          if (b[mid] - alreadyHave > k) {
            right = mid;
          } else {
            left = mid;
          }
        }
        assert(left >= cur);
        alreadyHave = b[left];
        cur = left + 1;
        curAns++;
      }
      answer[k] = curAns;
    }
    cout << answer[k] << '\n';
  }
}
```

