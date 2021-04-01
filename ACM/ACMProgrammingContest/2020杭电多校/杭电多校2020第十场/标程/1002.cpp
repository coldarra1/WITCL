#include <climits>
#include <vector>
#include <array>
#include <queue>
#include <utility>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <cassert>

template <typename T> using Vector  = std::vector<T>;
template <typename T> using Queue   = std::queue<T>;
template <typename T> using Pair    = std::array<T, 2>;

constexpr int NIL = INT_MAX;

int n;
Vector<Pair<int>>       edges;
Vector<int>             fid;
Vector<int>             pre;

class ForestOracle {
    Vector<int>             edgelist;
    Vector<Vector<int>>     incident;
    Vector<int>             parent;
    Vector<int>             peid;

    void dfs(int u, int p, int e = NIL) {
        if (parent[u] != NIL) return;
        parent[u] = p;
        peid[u] = e;
        for (int eid : incident[u]) 
            dfs(edges[eid][0] ^ edges[eid][1] ^ u, u, eid);
    }

public:
    explicit ForestOracle(int eid) : 
        incident(n), parent(n), peid(n), edgelist{eid} {}

    void insert(int eid) {
        edgelist.push_back(eid);
    }

    void remove(int eid) {
        edgelist.erase(std::find(edgelist.begin(), edgelist.end(), eid));
    }

    void prepare(int r) {
        for (auto& inc : incident) inc.clear();
        std::fill(parent.begin(), parent.end(), NIL);
        std::fill(peid.begin(), peid.end(), NIL);
        for (int eid : edgelist)
            for (int u : edges[eid])
                incident[u].push_back(eid);
        dfs(r, r);
    }

    bool get_cycle(Queue<int>& q, int eid) {
        int u = edges[eid][0], v = edges[eid][1];
        if (parent[u] == NIL || parent[v] == NIL) 
            return false;
        Vector<int> eids;
        for (int vtx : {u, v}) {
            while (parent[vtx] != vtx && pre[peid[vtx]] == NIL) {
                eids.push_back(peid[vtx]);
                vtx = parent[vtx];
            }
        }
        std::reverse(eids.begin(), eids.end());
        for (int e : eids) {
            pre[e] = eid;
            q.push(e);
        }
        return true;
    }
};

Vector<ForestOracle> forests;

void augment(int eid) {
    if (forests.empty()) {
        fid[eid] = 0;
        forests.emplace_back(eid);
        return;
    }
    Queue<int> q; q.push(eid);
    
    fid[eid] = -1;  // s.t. (fid[eid] + 1) mod k = 0
    std::fill(pre.begin(), pre.end(), NIL);
    while (q.size()) {
        int u = q.front(); q.pop();
        int nf = (fid[u] + 1) % forests.size();
        if (!forests[nf].get_cycle(q, u)) {
            while (u != eid) {
                forests[nf].insert(u);
                forests[fid[u]].remove(u);
                std::swap(fid[u], nf);
                u = pre[u];
            }
            forests[nf].insert(u);
            fid[u] = nf;
            return;
        }
    }
    fid[eid] = forests.size();
    forests.emplace_back(eid);
}

int main() {
    int T; std::cin >> T;
    while (T--) {
        forests.clear();

        int m;
        std::cin >> n >> m;
        edges.resize(m);
        fid.resize(m);
        pre.resize(m);
        for (int i = 0; i < m; i++) {
            for (int& u : edges[i]) {
                std::cin >> u;
                u--;
            }
            for (auto& f : forests) f.prepare(edges[i][0]);
            augment(i);
        }
        std::cout << forests.size() << std::endl;
    }
    return 0;
}