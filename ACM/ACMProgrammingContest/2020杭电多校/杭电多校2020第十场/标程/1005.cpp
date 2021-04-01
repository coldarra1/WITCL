#include <bits/stdc++.h>
using namespace std;

const int maxn = 5e5 + 7;

typedef pair<int, int> Pair;

int nodeL, edgeL;
int cnt_node[maxn], cnt_edge[maxn];
bool blocked[maxn];
int dep[maxn], anc[maxn], o[maxn], sz[maxn];
int allcount[maxn], W[maxn];
vector<Pair> e[maxn];

int find_root(int st) {
    anc[st] = -1;
    sz[st] = 1;
    W[st] = 0;
    int h = 0, t = 0;
    o[t] = st;
    while (h <= t) {
        int u = o[h++];
        for (auto &v : e[u]) {
            if (blocked[v.first]) continue;
            if (v.first == anc[u]) continue;
            anc[v.first] = u;
            o[++t] = v.first;
            sz[v.first] = 1;
            W[v.first] = 0;
        }
    }
    for (int i = t; i >= 1; i--) {
        sz[ anc[ o[i] ] ] += sz[ o[i] ];
        W[ anc[ o[i] ] ] = max(W[ anc[ o[i] ] ], sz[ o[i] ]);
    }


    int MX = sz[st], root = st;
    for (int i = 0; i <= t; i++) {
        W[ o[i] ] = max(W[ o[i] ], sz[st] - sz[ o[i] ]);
        if (W[ o[i] ] < MX) {
            MX = W[ o[i] ];
            root = o[i];
        }
    }
    return root;
}

int max_dep = 0;
void travel(int u) {
    static int o[maxn];
    int h = 0, t = -1;
    o[++t] = u;
    
    while (h <= t) {
        int u = o[h++];
        allcount[ dep[u] ]++;
        max_dep = max(max_dep, dep[u]);
        for (auto &v : e[u]) {
            if (v.first == anc[u]) continue;
            if (blocked[ v.first ]) continue;
            anc[ v.first ] = u;
            dep[ v.first ] = dep[u] + 1;
            o[++t] = v.first;
        }
    }
}

void travel2(int st) {
    static int c[maxn];

    int h = 0, t = -1;
    o[++t] = st;
    while (h <= t) {
        int u = o[h++];
        c[ dep[u] ]++;
        for (auto &v : e[u]) {
            if (blocked[v.first]) continue;
            if (v.first == anc[u]) continue;
            o[++t] = v.first;
        }
    }
    int MX = dep[ o[t] ];
    for (int i = MX - 1; i >= 0; i--) c[i] += c[i + 1];

    for (int i = 0; i <= t; i++) {
        int u = o[i];
        int D = max(0, nodeL - dep[u] + 1);
        cnt_node[u] += allcount[D] - c[D];

        D = max(0, edgeL - dep[u] + 2);
        for (auto &v : e[u]) {
            if (v.first != anc[u]) continue;
            cnt_edge[v.second] += allcount[D] - c[D];
            if (dep[u] == 1) {
                D = edgeL + 2;
                cnt_edge[v.second] += c[D];
            }
        }
    }

    for (int i = 0; i <= MX; i++) c[i] = 0;
}

void work(int u) {
    int root = find_root(u);


    anc[root] = -1;
    dep[root] = 0;
    max_dep = 0;
    travel(root);
    for (int i = max_dep - 1; i >= 0; i--) allcount[i] += allcount[i + 1];

    cnt_node[root] += allcount[nodeL + 1];
    for (auto &v : e[root]) {
        if (blocked[v.first]) continue;
        travel2(v.first);
    }

    for (int i = 0; i <= max_dep; i++) allcount[i] = 0;

    blocked[root] = true;
    for (auto &v : e[root]) {
        if (blocked[v.first]) continue;
        work(v.first);
    }
}

int work() {



    int n, k;
    scanf("%d%d", &n, &k);
    nodeL = k / 2;
    edgeL = (k - 1) / 2;

    for (int i = 1; i <= n; i++) {
        e[i].clear();
        cnt_node[i] = 0;
        cnt_edge[i] = 0;
        blocked[i] = false;
    }

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        e[u].push_back(Pair(v, i));
        e[v].push_back(Pair(u, i));
    }

    work(1);

    int ans = n;
    for (int i = 1; i <= n; i++) { 
        ans = min(cnt_node[i], ans);
    }
    for (int i = 1; i <= n - 1; i++) {
        ans = min(cnt_edge[i], ans);
    }
    cout << ans << endl;
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        work();
    }
}