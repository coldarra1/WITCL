#include<bits/stdc++.h>
using namespace std;
const int MAX_N = 1000000;
const int MAX_M = 1000000;
int to[MAX_N];
int num[MAX_N];
int st[MAX_N], ed[MAX_N], nxt[MAX_N];
vector<int> e[MAX_N];
int find(int x) {
    if(x == to[x]) return x;
    return to[x] = find(to[x]);
}
bool join(int x, int y) {
    x = find(x);
    y = find(y);
    if(x == y)return 0;
    to[x] = y;
    return 1;
}
bool exist(int x) {
    return x == to[x];
}
void init(int n) {
    for(int i = 0; i < n; i++) e[i].clear();
    for(int i = 0; i < n; i++) {
        to[i] = i;
        num[i] = 1;
        st[i] = ed[i] = i;
        nxt[i] = -1;
    }
}
void merge(int z, int x) {
    if(st[z] == -1) return;
    if(st[x] == -1) {
        st[x] = st[z];
        ed[x] = ed[z];
    } else {
        nxt[ed[x]] = st[z];
        ed[x] = ed[z];
    }
}
void solve(){
    int n,m;
    scanf("%d%d", &n, &m);
    init(n);
    for(int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    int q;
    scanf("%d", &q);
    for(int i = 0; i < q; i++) {
        int x;
        scanf("%d", &x);
        if(!exist(x)) continue;
        if(st[x] == -1) continue;
        int it = st[x];
        st[x] = -1;
        while(it != -1) {
            for(int y:e[it]) {
                int z = find(y);
                if(join(z, x)) {
                    merge(z, x);
                }
            }
            it = nxt[it];
        }
    }
    for(int i = 0 ; i < n; i++) {
        printf("%d", find(i));
        if(i < n - 1) printf(" ");
        else puts("");
    }
}
#include <sys/resource.h>
bool increase_stack_size( int size_mb ) {
    struct rlimit rl;
    if ( getrlimit(RLIMIT_STACK,&rl)!=0 ) return 0;
    rl.rlim_cur=size_mb*(1<<20);
    if ( rl.rlim_cur>rl.rlim_max ) rl.rlim_cur=rl.rlim_max;
    return setrlimit(RLIMIT_STACK,&rl)==0;
}
int main() {
    increase_stack_size(256);
    int T;
    scanf("%d", &T);
    while(T--) {
        solve();
    }
}
