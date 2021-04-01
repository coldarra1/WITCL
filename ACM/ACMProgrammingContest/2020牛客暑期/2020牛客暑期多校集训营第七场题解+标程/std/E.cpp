#include <bits/stdc++.h>

#define long std::int64_t
const int MAXN = 520;
const int NIL = INT_MIN;
const long INF = INT64_MAX / MAXN / MAXN / MAXN;

template <typename T>
using Vector = std::vector<T>;

template <typename T>
using Matrix = Vector<Vector<T>>;

// compute the *maximum* weighted bipartite matching
// time complexity: O(mn^2)
template <typename T>
class KuhnMunkres {
    static constexpr T  MAX = std::numeric_limits<T>::max();
    static constexpr T  MIN = std::numeric_limits<T>::min();
    int             n, m;       // sizes of left part and right part
    Matrix<T>       w;          // weight matrix
    Vector<T>       lp, rp;     // potential of vertices
    Vector<T>       slack;      // slack values for right vertices
    Vector<int>     lm, rm;     // left & right match
    Vector<int>     pre;        // previous vertex during bfs
    Vector<char>    vis;        // right vertex visited in Hungarian tree
    T               cost;       // current total cost

    void bfs(int src) {
        std::fill(vis.begin(), vis.end(), false);
        // convert MAX to rvalue of T to avoid odr-use
        std::fill(slack.begin(), slack.end(), T(MAX));  
        std::fill(pre.begin(), pre.end(), m);

        rm[m] = src;
        int v = m;
        while (rm[v] != NIL) {
            T delta = MAX;
            int next = NIL;
            int u = rm[v];
            vis[v] = true;
            for (int j = 0; j < m; j++) if (!vis[j]) {
                T gap = lp[u] + rp[j] - w[u][j];
                if (slack[j] > gap) {
                    slack[j] = gap;
                    pre[j] = v;
                }
                if (slack[j] < delta) {
                    delta = slack[j];
                    next = j;
                }
            }
            for (int j = 0; j <= m; j++) {
                if (vis[j]) {
                    lp[rm[j]] -= delta;
                    rp[j] += delta;
                } else {
                    slack[j] -= delta;
                }
            }
            v = next;
        }
        while (v != m) {
            rm[v] = rm[pre[v]];
            v = pre[v];
        }
    }

public:
    KuhnMunkres(Matrix<T> wm) : 
        n(wm.size()), m((assert(n > 0), wm[0].size())), w(std::move(wm)), 
        lp(n), rp(m + 1), slack(m), vis(m + 1), lm(n), rm(m + 1, NIL), pre(m)
    {
        assert(n <= m);
    }

    T perfect_matching() {
        for (int u = 0; u < n; u++) bfs(u);
        cost = 0;
        for (int v = 0; v < m; v++) if (rm[v] != NIL) {
            cost += w[rm[v]][v];
            lm[rm[v]] = v;
        }
        return cost;
    }

    // compute the reverse flow from every left vertex
    // using Floyd-Warshall algorithm
    Vector<T> reverse_flow() {
        Matrix<T> dist(n, Vector<T>(n));
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                dist[i][j] = -w[i][lm[i]] + w[j][lm[i]];
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    dist[i][j] = std::max(dist[i][j], dist[i][k] + dist[k][j]);
        Vector<T> ret(n, T(MIN));
        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++)
                ret[i] = std::max(ret[i], dist[i][j] - w[j][lm[j]]);
        for (T& val : ret) val += cost;
        return ret;
    }
};

int n, m, id = 0;
Vector<int> ta[MAXN], tb[MAXN];
int cost_per_copy[MAXN];
int eid[MAXN][MAXN];
long dp[MAXN][MAXN * 3], dp2[MAXN];

void dfs(int u, int p) {
    for (int v : ta[u]) if (v != p) dfs(v, u);
    dp2[u] = INF;
    for (int v = 1; v <= m; v++) {
        // handle some special cases here
        if (ta[u].size() < tb[v].size()) continue;
        if (tb[v].size() == 0) {
            long cost = cost_per_copy[v];
            for (int ch : ta[u]) cost += dp2[ch];
            dp2[u] = std::min(dp2[u], cost);
            continue;
        }

        // compute the weighted bipartite matching
        int nl = tb[v].size(), nr = ta[u].size();
        Matrix<long> w(nl, Vector<long>(nr));
        long base_cost = 0;
        for (int rv : ta[u]) base_cost += dp2[rv];
        for (int i = 0; i < nl; i++) {
            int bi = tb[v][i];
            for (int j = 0; j < nr; j++) {
                int aj = ta[u][j];
                w[i][j] = dp[aj][eid[v][bi]];
                if (w[i][j] < INF) w[i][j] -= dp2[aj];
            }
        }
        for (int i = 0; i < nl; i++)
            for (int j = 0; j < nr; j++)
                w[i][j] = -w[i][j];
        KuhnMunkres<long> matcher(std::move(w));
        long matching_cost = -matcher.perfect_matching() + base_cost;
        dp2[u] = std::min(dp2[u], matching_cost + cost_per_copy[v]);
        auto rev = matcher.reverse_flow();
        for (int i = 0; i < nl; i++) {
            int bi = tb[v][i];
            dp[u][eid[bi][v]] = std::min(dp[u][eid[bi][v]], -rev[i] + base_cost);
        }
    }
}

int main() {
    std::cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        ta[u].push_back(v);
        ta[v].push_back(u);
    }
    int ns; std::cin >> ns;
    while (ns--) {
        int n, c; std::cin >> n >> c;
        for (int i = 1; i < n; i++) {
            int u, v; 
            std::cin >> u >> v;
            u += m; v += m;
            tb[u].push_back(v);
            tb[v].push_back(u);
            eid[u][v] = id++;
            eid[v][u] = id++;
        }
        for (int i = 1; i <= n; i++)
            cost_per_copy[m + i] = c;
        m += n;
    }
    for (int i = 1; i <= n; i++) std::fill(dp[i], dp[i] + id, INF);
    dfs(1, 0);
    if (dp2[1] >= INF) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << dp2[1] << std::endl;
    }
    return 0;
}
