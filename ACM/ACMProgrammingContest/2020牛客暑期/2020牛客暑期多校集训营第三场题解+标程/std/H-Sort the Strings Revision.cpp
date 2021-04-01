#include<bits/stdc++.h>
using namespace std;
//#define TRACE
const int MOD = 1000000007;
const int MUL = 10000019;
const int MAX_N = 10000000;
bitset<MAX_N> d, same;
int p[MAX_N];
int n;
int stk_pos[MAX_N];
int stk_v[MAX_N];
int son[MAX_N][2];
int ans[MAX_N + 2];
void get_permutation(){
    scanf("%d", &n);
    memset(ans, 0, sizeof(int) * (n + 1));
    memset(son,-1,sizeof(int) * n * 2);
    for(int i = 0; i < n; i++) same[i] = 0;
    int v, a, b, mod;
    p[0] = 0;
    scanf("%d%d%d%d", &v, &a, &b, &mod);
    for(int i = 1; i < n; i++) {
        int id = v % (i + 1);
        p[i] = p[id];
        p[id] = i;
        v = ((long long)v * a + b) % mod;
    }
}
void dfs(int x, int l, int r){
    if(d[x]) {
        int v = x - l + 1;
        ans[x + 1] += v;
        ans[r + 1] -= v;
    }
    else {
        int v = r - x;
        ans[l] += v;
        ans[x + 1] -= v;
    }
    if(son[x][0] != -1) dfs(son[x][0], l, x);
    if(son[x][1] != -1) dfs(son[x][1], x + 1, r);
}
void solve(){
    get_permutation();
#ifdef TRACE
    printf("p:");
    for(int i=0;i<n;i++)printf("%d%c",p[i]," \n"[i==n-1]);
    printf("v:");
#endif
    int v, a, b, mod;
    scanf("%d%d%d%d", &v, &a, &b, &mod);
    int sn = -1;
    for(int i = 0; i < n; i++) {
        if(i) {
            v = ((long long)v * a + b) % mod;
        }
#ifdef TRACE
        printf("%d%c",v % 10," \n"[i==n-1]);
#endif
        int dif = v % 10 - p[i] % 10;
        if(!dif) {
            same[i] = 1;
            continue;
        }
        if(dif>0) {
            d[i] = 1;
        }
        else {
            d[i] = 0;
        }
        int tmp_p = p[i];
        while(sn >= 0 && stk_v[sn] > tmp_p) {
            son[i][0] = stk_pos[sn];
            sn--;
        }
        if(sn >= 0) {
            son[stk_pos[sn]][1] = i;
        }
        stk_pos[++sn] = i;
        stk_v[sn] = tmp_p;
    }
    if(sn >= 0) {
        dfs(stk_pos[0], 0, n);
    }
    long long mul = 1;
    int compressed_ans = 0;
    for(int i = 0; i <= n; i++) {
        ans[i + 1] += ans[i];
        if(i && same[i - 1]) ans[i] = ans[i - 1] + 1;
        compressed_ans = (compressed_ans + mul * ans[i]) % MOD;
        mul = mul * MUL % MOD;
    }
#ifdef TRACE
    printf("ans:");
    for(int i=0;i<=n;i++)printf("%d%c",ans[i]," \n"[i==n]);
#endif
    printf("%d\n", compressed_ans);
}
int main() {
    int T;
    scanf("%d", &T);
    for(int tt = 1; tt <= T; tt++) {
        solve();
    }
    return 0;
}
