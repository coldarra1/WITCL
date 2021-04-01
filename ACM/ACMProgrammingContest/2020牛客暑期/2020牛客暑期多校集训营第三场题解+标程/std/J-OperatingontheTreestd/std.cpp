#include<bits/stdc++.h>
using namespace std;
const int MOD = 998244353;
const int MAX_N = 2000;
vector<int> e[MAX_N];
int n;
int num[MAX_N];
int C[MAX_N][MAX_N];
int dp_num[MAX_N][3][MAX_N];
int dp_sum[MAX_N][3][MAX_N];
void ADD(int &x, long long v) {x = (x + v) % MOD;}
int get(int d[], int l, int r) {
    if(l > r) return 0;
    if(!l) return d[r];
    int v = d[r] - d[l - 1];
    if(v < 0) v += MOD;
    return v;
}
void init() {
    for(int i = 0; i < n; i++) e[i].clear();
}
int tmp_num[3][MAX_N], tmp_sum[3][MAX_N];
void merge_to(int x, int y, int tar, int src1, int src2, int i, int j, int l,int r) {
    ADD(tmp_num[tar][i + j], (long long)dp_num[x][src1][i] * get(dp_num[y][src2], l, r) % MOD * 
            C[i+j][i] % MOD * C[(num[x] - i - 1) + (num[y] - j)][num[y] - j]);
    ADD(tmp_sum[tar][i + j], (long long)dp_sum[x][src1][i]* get(dp_num[y][src2], l, r) % MOD * 
            C[i+j][i] % MOD * C[(num[x] - i - 1) + (num[y] - j)][num[y] - j]);
    ADD(tmp_sum[tar][i + j], (long long)dp_num[x][src1][i] * get(dp_sum[y][src2], l, r) % MOD * 
            C[i+j][i] % MOD * C[(num[x] - i - 1) + (num[y] - j)][num[y] - j]);
}
void dfs(int x) {
    num[x] = 1;
    dp_num[x][1][0] = 0;
    dp_num[x][0][0] = dp_num[x][2][0] = 1;
    dp_sum[x][1][0] = dp_sum[x][0][0] = 0;
    dp_sum[x][2][0] = 1;
    for(int y: e[x]) {
        dfs(y);
        for(int i = 0; i < 3; i++) {
            memset(tmp_num[i], 0, sizeof(int) * (num[x] + num[y]));
            memset(tmp_sum[i], 0, sizeof(int) * (num[x] + num[y]));
        }
        for(int i = 0; i < num[x]; i++) {
            for(int j = 0; j <= num[y]; j++) {
                merge_to(x, y, 2, 2, 1, i, j, 0, num[y] - 1);
                merge_to(x, y, 2, 2, 0, i, j, j, num[y] - 1);
                
                merge_to(x, y, 1, 1, 2, i, j, 0, num[y] - 1);
                merge_to(x, y, 1, 1, 1, i, j, 0, num[y] - 1);
                merge_to(x, y, 1, 0, 2, i, j, 0, j - 1);
                
                merge_to(x, y, 0, 0, 2, i, j, j, num[y] - 1);
                merge_to(x, y, 0, 0, 1, i, j, 0, num[y] - 1);
            }
        }
        num[x] += num[y];
        for(int i = 0; i < 3; i++) {
            memcpy(dp_num[x][i], tmp_num[i], sizeof(int) * num[x]);
            memcpy(dp_sum[x][i], tmp_sum[i], sizeof(int) * num[x]);
        }
    }
    for(int i = 0; i < 3; i++) {
        for(int j = 1; j < num[x]; j++) {
            ADD(dp_num[x][i][j], dp_num[x][i][j - 1]);
            ADD(dp_sum[x][i][j], dp_sum[x][i][j - 1]);
        }
    }
}
void solve() {
    scanf("%d", &n);
    init();
    for(int y = 1; y < n; y++) {
        int x;
        scanf("%d", &x);
        e[x].push_back(y);
    }
    dfs(0);
    int an = 0;
    ADD(an, dp_sum[0][1][n - 1] + dp_sum[0][2][n - 1]);
    printf("%d\n", an);
}
int main() {
    for(int i = 0; i < MAX_N; i++) {
        C[i][0] = 1;
        for(int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            if(C[i][j] >= MOD) C[i][j] -= MOD;
        }
    }
    int T;
    scanf("%d", &T);
    for(int i = 1; i <= T; i++) solve();
    return 0;
}