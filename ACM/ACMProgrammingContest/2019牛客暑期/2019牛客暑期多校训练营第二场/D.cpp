// Author: Yen-Jen Wang
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

const __int128 ONE = 1;
const int MAX_N = 100 + 7;

int N, K;
int W[MAX_N];
vector<int> odr;
__int128 G[MAX_N];
char S[MAX_N][MAX_N];

void input() {
    scanf("%d%d", &N, &K);
    for (int i = 0; i < N; i++) 
        scanf("%d", &W[i]);
    for (int i = 0; i < N; i++) {
        scanf("%s", S[i]);
        for (int j = 0; j < N; j++)
            S[i][j] -= '0';
    }
}

int popcount(__int128 x) {
    return __builtin_popcountll(x >> 50) + __builtin_popcount(x & ((ONE << 50) - 1));
}

int lowbit(__int128 x) {
    if ((x & ((ONE << 50) - 1)) == 0)
        return __builtin_ctzll((ll)(x >> 50)) + 50;
    else
        return __builtin_ctzll((ll)(x & ((ONE <<50) - 1)));
}

void build() {
    for (int i = 0; i < N; i++)
        odr.push_back(i);
    sort(odr.begin(), odr.end(), [&] (const int x, const int y) {
        return W[x] < W[y];
    });

    static int mapping[MAX_N];
    for (int i = 0; i < N; i++)
        mapping[odr[i]] = i;

    static int W_tmp[MAX_N];
    for (int i = 0; i < N; i++)
        W_tmp[i] = W[i];
    for (int i = 0; i < N; i++) 
        W[mapping[i]] = W_tmp[i];
    
    static char S2[MAX_N][MAX_N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) 
            S2[i][j] = S[i][j];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) 
            S[mapping[i]][mapping[j]] = S2[i][j];
    }
    for (int i = 0; i < N; i++) {
        G[i] = 0;
        for (int j = 0; j < N; j++) {
            if (S[i][j]) {
                G[i] |= (ONE << j);
            }
        }
    }
}

int cnt;
ll limit;

void dfs(__int128 now, __int128 can, ll sum) {
    if (sum <= limit)
        cnt++;
    else
        return;
    
    if (cnt >= K)
        return;

    while (can) {
        int p = lowbit(can);
        can ^= (ONE << p);

        dfs(now | (ONE << p), can & G[p], sum + W[p]);

        //if ((now & G[p]) != now)
            //continue;
        
        if (sum + W[p] > limit)
            break;
        
        //dfs(now | (ONE << p), can, sum + W[p]);
        
        if (cnt >= K)
            break;
    }
}

bool check(ll x) {
    cnt = 0;
    limit = x;
    dfs(0, (ONE << N) - 1, 0);
    return cnt >= K;
}

void solve() {    
    ll lb = 0, rb = 0;
    for (int i = 0; i < N; i++)
        rb += W[i];
    while (lb < rb) {
        ll mid = (lb + rb) >> 1;
        if (check(mid))
            rb = mid;
        else
            lb = mid + 1;
    }
    if (check(lb))
        printf("%lld\n", lb);
    else
        puts("-1");
}

int main() {
    input();
    build();
    solve();
    return 0;
}
