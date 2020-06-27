# 解题报告

## King's Children

如果不需要最大化矩形$A$的面积，则可以用如下算法解决该问题。垂直拉伸每个字母，直到碰到另一个字母或王国的边界。这样，我们得到了一组完整的列。水平拉伸每一列，直到碰到另一个字母或王国的边界。

考虑如何最大化矩形$A​$的面积。首先，找到包含字母$A​$且不包含其他字母的最大面积的矩形。这是一个可以在时间$O(nm)​$中解决的标准问题。显然王国的其余部分仍可以按要求的方式分成矩形。因为我们可以将剩下的区域分为四个大矩形：矩形$A​$的上，下，左，右侧（左上，左下，右上，右下可并到任意一个相邻的大矩形中）。每个大矩形都包含至少一个字母（否则我们可以在相应的方向上放大矩形$A​$）。对于剩下的四个大矩形分别采取最开始的算法即可。解决该问题的总时间复杂度为$O(nm)​$

$Std:​$

```c++
#include <bits/stdc++.h>

#define long long long int

using namespace std;

// @author: pashka

void fill(vector<string> &a, int U, int B, int L, int R, char c) {
    for (int i = U; i < B; i++) {
        for (int j = L; j < R; j++) {
            a[i][j] = c;
        }
    }
}

char lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        c = 'a' + (c - 'A');
    }
    return c;
}

void split(vector<string> &a, int U, int B, int L, int R) {
    for (int i = U + 1; i < B; i++) {
        for (int j = L; j < R; j++) {
            if (a[i][j] == '.') {
                a[i][j] = lower(a[i - 1][j]);
            }
        }
    }
    for (int i = B - 2; i >= U; i--) {
        for (int j = L; j < R; j++) {
            if (a[i][j] == '.') {
                a[i][j] = lower(a[i + 1][j]);
            }
        }
    }
    for (int i = U; i < B; i++) {
        for (int j = L + 1; j < R; j++) {
            if (a[i][j] == '.') {
                a[i][j] = lower(a[i][j - 1]);
            }
        }
    }
    for (int i = U; i < B; i++) {
        for (int j = R - 2; j >= L; j--) {
            if (a[i][j] == '.') {
                a[i][j] = lower(a[i][j + 1]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int ar = -1, ac = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i][j] == 'A') {
                ar = i;
                ac = j;
            }
        }
    }
    a[ar][ac] = '.';

    int maxS = -1;
    int bestL = -1;
    int bestR = -1;
    int bestU = -1;
    int bestB = -1;
    vector<int> up(m + 1);
    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> s;
        for (int j = 0; j <= m; j++) {
//            cout << i << " " << j << "\n";
            if (j == m || a[i][j] != '.') {
                up[j] = i + 1;
            }
            int x = j;
            while (!s.empty() && s.back().second < up[j]) {
                int L = s.back().first;
                int R = j;
                int U = s.back().second;
                int B = i + 1;
                if (U <= ar && ar < B && L <= ac && ac < R) {
                    int S = (R - L) * (B - U);
                    if (S > maxS) {
                        maxS = S;
                        bestL = L;
                        bestR = R;
                        bestU = U;
                        bestB = B;
                    }
                }
                x = s.back().first;
                s.pop_back();
            }
            s.push_back({x, up[j]});
        }
    }
//    cout << bestU << " " << bestB << " " << bestL << " " << bestR << "\n";
    fill(a, bestU, bestB, bestL, bestR, 'a');

    split(a, 0, bestU, 0, m);
    split(a, bestB, n, 0, m);
    split(a, bestU, bestB, 0, bestL);
    split(a, bestU, bestB, bestR, m);

    a[ar][ac] = 'A';

    for (int i = 0; i < n; i++) {
        cout << a[i] << "\n";
    }

    return 0;
}
```

