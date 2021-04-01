#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <ccomplex>
#include <cfenv>
#include <cinttypes>
#include <cstdbool>
#include <cstdint>
#include <ctgmath>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#define mp make_pair
#define pb push_back
#define left lef
#define right righ
#define rep(i,n) for(long long i=1;i<=n;++i)
#define bit(i) __builtin_popcount(i)
#define x1 gtmsub
#define y1 gtmshb
#define x2 gtmjtjl
#define y2 gtmsf
using namespace std;
#define N 100020
#define LL long long 
struct SegTree {
    LL lazy[N*4], sum[N*4];
    int n;
    void init(int n1) {
        n = n1;
        memset(lazy, 0, sizeof(lazy));
        memset(sum , 0, sizeof(sum ));
    }
    void pushdown(int p, int left, int right) {
        if (lazy[p]) {
            sum[p] += lazy[p] * (right - left + 1);
            if (left != right) lazy[p<<1|0] += lazy[p], lazy[p<<1|1] += lazy[p];
            lazy[p] = 0;
        }
    }
    void pushup(int p, int left, int right) {
        int mid = (left + right) >> 1;
        pushdown(p<<1|0, left, mid);
        pushdown(p<<1|1, mid+1, right);
        sum[p] = sum[p<<1|0] + sum[p<<1|1];
    }
    void add(int p, int left, int right, int x, int y) {
        pushdown(p, left, right);
        if (x <= left && right <= y) {
            lazy[p] ++;
            pushdown(p, left, right);
            return;
        }
        int mid = (left + right) >> 1;
        if (x <= mid) add(p<<1|0, left, mid, x, y);
        if (y >  mid) add(p<<1|1, mid+1, right, x, y);
        pushup(p, left, right);
    }
    void add(int x, int y) { add(1, 1, n, x, y); }
    LL get(int p, int left, int right, int x, int y) {
        pushdown(p, left, right);
        if (x <= left && right <= y) {
            return sum[p];
        }
        int mid = (left + right) >> 1;
        LL s = 0;
        if (x <= mid) s += get(p<<1|0, left, mid, x, y);
        if (y >  mid) s += get(p<<1|1, mid+1, right, x, y);
        return s;
    }
    LL get(int x, int y) { if (x>y) return 0; return get(1, 1, n, x, y); }
} tree;
 
struct EDGE {
    int adj, next;
} edge[N*2];
int n, q, top, to, gh[N];
int deep[N], father[N], son[N], size[N], Top[N], w[N];
LL answ, ans;
 
void addedge(int x, int y) {
    edge[++top].adj = y;
    edge[top].next = gh[x];
    gh[x] = top;
}
 
void dfs(int x, int root=0) {
    father[x] = root;
    deep[x] = deep[root] + 1;
    son[x] = 0; size[x] = 1;
    int dd = 0;
    for (int p=gh[x]; p; p=edge[p].next)
        if (edge[p].adj != root) {
            dfs(edge[p].adj, x);
            size[x] += size[edge[p].adj];
            if (size[edge[p].adj] > dd) {
                dd = size[edge[p].adj];
                son[x] = edge[p].adj;
            }
        }
}
 
void split(int x, int tp) {
    w[x] = ++to; Top[x] = tp;
    if (son[x]) split(son[x], tp);
    for (int p=gh[x]; p; p=edge[p].next)
        if (edge[p].adj != father[x] && edge[p].adj != son[x])
            split(edge[p].adj, edge[p].adj);
}
void Init() {
    memset(gh, 0, sizeof(gh));
    top = to = 0;
    scanf("%d%d", &n, &q);
    for (int i=1;i<n;i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        addedge(x, y);
        addedge(y, x);
    }
    dfs(1); split(1, 1);
    tree.init(n);
}
 
LL query(int x, bool isq) {
    int tx = Top[x]; LL anscnt = 0;
    while (tx != 1) {
        if (isq) anscnt += tree.get(w[tx], w[x]);
        else               tree.add(w[tx], w[x]);
        x = father[tx];
        tx = Top[x];
    }
    if (isq) anscnt += tree.get(w[1]+1, w[x]);
    else               tree.add(w[1]  , w[x]);
    return anscnt;
}
LL delta[N];
LL get(int x)
{
	LL ans=0;
	ans = 2LL * query(x, true);
    ans += answ;
    ans += -tree.get(w[1], w[1]) * (deep[x]-1);
    return ans+delta[x];
}
void Solve() {
    // Ans = sum(root) + dep(i) * cnt(root) - 2 sigma cnt(i) (i belongs to i --> root and root is not included)
    int oper, x, d; answ = 0;
    memset(delta,0,sizeof(delta));
    while (q--) {
        scanf("%d", &oper);
        if (oper == 1)
        {
        	scanf("%d%d", &x, &d);
            answ += d - deep[x] + 1;
            query(x, false);
        }
        else 
        if (oper == 2)
        {
			scanf("%d",&x);
        	LL tdelta=max(0ll,get(x));
        	delta[x]-=tdelta;
        }
        else
        if (oper == 3)
        {
        	scanf("%d", &x);
            printf("%lld\n", get(x));
        }
    }
}
 
int main() {
	int T;
	cin>>T;
	while (T--)
	{
		Init();
    	Solve();
	}
    return 0;
}