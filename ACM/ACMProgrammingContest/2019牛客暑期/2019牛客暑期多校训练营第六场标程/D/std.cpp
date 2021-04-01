//
// Created by Wu Junjie on 2019-06-30.
//

#include <bits/stdc++.h>

const int MAXN = 1010;

int n, k;
int v[MAXN];

bool check(int V) {
    std::multiset<int> multiset;
    for (int i = 1; i <= n; ++i) {
        multiset.insert(v[i]);
    }
    for (int i = 1; i <= k && !multiset.empty(); ++i) {
        int now = V;
        while (now && !multiset.empty()) {
            auto it = multiset.upper_bound(now);
            if (it == multiset.begin()) {
                break;
            }
            --it;
            now -= *it;
            multiset.erase(it);
        }
    }
    return multiset.empty();
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cs = 1; cs <= T; ++cs) {
        scanf("%d%d", &n, &k);
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            scanf("%d", v + i);
            sum += v[i];
        }
        sum = (sum + k - 1) / k;
        for (int i = sum; ; ++i) {
            if (check(i)) {
                printf("Case #%d: %d\n", cs, i);
                break;
            }
        }
    }
    return 0;
}