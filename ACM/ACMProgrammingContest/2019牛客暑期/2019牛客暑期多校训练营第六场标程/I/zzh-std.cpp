#include <bits/stdc++.h>

const int moder = 998244353;
const int N = 200010;
typedef std::pair<int, int> pii;
typedef std::pair <pii, int> piii;

bool vis[N], instack[N];
int inv[N];
std::vector<piii> stack;
std::vector<pii> e[N], _e[N];
int n, m, pcnt;
int ans[N];

void dfs(int u, int fa, int prob) {
    vis[u] = true;
    instack[u] = true;
    stack.push_back({{u, prob}, 0});
    for (auto p : e[u]) {
        int v = p.first;
        if (!vis[v]) {
            dfs(v, u, p.second);
            continue;
        }
        if (instack[v] && v != fa) {
            ++pcnt;
            for (int i = (int) stack.size() - 1; i >= 0 && stack[i].first.first != v; --i) {
                int w = stack[i].first.first;
                stack[i].second = 1;
                _e[w].push_back({pcnt, stack[i].first.second});
                _e[pcnt].push_back({w, stack[i].first.second});
            }
            _e[v].push_back({pcnt, p.second});
            _e[pcnt].push_back({v, p.second});
        }
    }
    if ((int) stack.size() >= 2 && !stack.back().second) {
        int v = stack[stack.size() - 2].first.first;
        _e[u].push_back({v, stack.back().first.second});
        _e[v].push_back({u, stack.back().first.second});
    }
    stack.pop_back();
    instack[u] = false;
}

void calc(int u, int fa, int prob){
    if (u > n){
        int sz = _e[u].size();
        for (int i = 0; i < sz; ++ i){
            if (_e[u][i].first == fa){
                std::rotate(_e[u].begin(), _e[u].begin() + i, _e[u].end());
                break;
            }
        }
        std::vector <int> pre(sz), suf(sz);
        pre[0] = 1;
        for (int i = 1; i < sz; ++ i){
            pre[i] = 1ll * pre[i - 1] * _e[u][i - 1].second % moder;
        }
        suf[sz - 1] = _e[u][sz - 1].second;
        for (int i = sz - 2; i >= 1; -- i){
            suf[i] = 1ll * suf[i + 1] * _e[u][i].second % moder;
        }
        for (int i = 1; i < sz; ++ i){
            int nprob = 1ll * prob * (1 - 1ll * (1 - pre[i]) * (1 - suf[i]) % moder) % moder;
            nprob += nprob < 0 ? moder : 0;
            calc(_e[u][i].first, u, nprob);
        }
        return;
    }
    ans[u] = prob;
    for (auto p : _e[u]){
        int v = p.first;
        if (v == fa){
            continue;
        }
        if (v > n){
            calc(v, u, prob);
        }
        else{
            calc(v, u, 1ll * prob * p.second % moder);
        }
    }
}

int solve(){
    memset(vis, 0, sizeof(vis));
    memset(instack, 0, sizeof(instack));
    for (int i = 0; i < N; ++ i){
        e[i].clear();
        _e[i].clear();
    }
    stack.clear();
    scanf("%d%d", &n, &m);
    for (int i = 0, u, v, a, b; i < m; ++i) {
        scanf("%d%d%d%d", &u, &v, &a, &b);
        a = 1ll * a * inv[b] % moder;
        e[u].push_back({v, a});
        e[v].push_back({u, a});
    }
    pcnt = n;
    dfs(1, 0, 0);
    calc(1, 0, 1);
    int sum = 0;
    for (int i = 1; i <= n; ++ i){
        sum += ans[i];
        sum -= sum >= moder ? moder : 0;
    }
    return sum;
}

int main(){
    inv[1] = 1;
    for (int i = 2; i < N; ++ i){
        inv[i] = moder - 1ll * (moder / i) * inv[moder % i] % moder;
    }
    int test;
    scanf("%d", &test);
    for (int i = 1; i <= test; ++ i){
        printf("Case #%d: %d\n", i, solve());
    }
    return 0;
}
