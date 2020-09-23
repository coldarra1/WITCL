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


