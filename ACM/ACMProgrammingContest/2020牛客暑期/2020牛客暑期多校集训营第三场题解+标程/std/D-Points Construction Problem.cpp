#include<bits/stdc++.h>
void noSolution() {
    puts("No");
}
int u[1000][1000], tt;
void solve() {
    int n,k;
    scanf("%d%d", &n, &k);
    if(k % 2 || k > 4 * n) {
        noSolution();
        return;
    }
    int h = 1, w = 1;
    while(h * w < n) {
        if(h <= w) h++;
        else w++;
    }
    if((h + w) * 2 > k) {
        noSolution();
        return;
    }
    tt++;
    std::pair<int, int> grid[100];
    int it = 0;
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            if(it < n) {
                u[i][j] = tt;
                grid[it++] = std::make_pair(i, j);
            }
        }
    }
    int top_y = 1;
    int now_k = 2 * (h + w);
    it--;
    while(now_k < k) {
        int v=0;
        if(u[grid[it].first - 1][grid[it].second] == tt) v++;
        if(u[grid[it].first][grid[it].second - 1] == tt) v++;
        if(now_k + 2 * v <= k) {
            now_k += 2 * v;
            grid[it] = std::make_pair(20, top_y);
            top_y += 2;
        }
        else {
            now_k += 2;
            grid[it] = std::make_pair(1, w + 1);
        }
        it--;
    }
    puts("Yes");
    for(int i = 0; i < n; i++) printf("%d %d\n",grid[i].first, grid[i].second);
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) solve();
    return 0;
}
