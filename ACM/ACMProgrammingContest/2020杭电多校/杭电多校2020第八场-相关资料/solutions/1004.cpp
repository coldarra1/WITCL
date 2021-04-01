#include <bits/stdc++.h>
using namespace std;
#define N 300000 + 5

int n, m, q, E[N][2], Max[N], Stack[N];

struct Node
{
    int l, r, fa, pre;
    bool flag;
}h[N];

void init()
{
    memset(h,0,sizeof(h));
    memset(E,0,sizeof(E));
    memset(Max,0,sizeof(Max));
    memset(Stack,0,sizeof(Stack));
}

inline void swap(int &u, int &v)
{
    u = u + v, v = u - v, u = u - v;
}

inline void zig(int x)
{
    int y = h[x].fa, z = h[y].fa;
    if (y == h[z].l) h[z].l = x;
    if (y == h[z].r) h[z].r = x;
    h[x].fa = z, h[y].fa = x;
    h[y].l = h[x].r, h[h[x].r].fa = y, h[x].r = y;
}

inline void zag(int x)
{
    int y = h[x].fa, z = h[y].fa;
    if (y == h[z].l) h[z].l = x;
    if (y == h[z].r) h[z].r = x;
    h[x].fa = z, h[y].fa = x;
    h[y].r = h[x].l, h[h[x].l].fa = y, h[x].l = y;
}

inline void push(int x)
{
    if (h[x].flag)
    {
        h[h[x].l].flag ^= 1;
        h[h[x].r].flag ^= 1;
        swap(h[x].l, h[x].r);
        h[x].flag = 0;
    }
}

inline void Splay(int x)
{
    int rt = x;
    for (; h[rt].fa; rt = h[rt].fa) Stack[++ Stack[0]] = rt;
    push(rt);
    while (Stack[0]) push(Stack[Stack[0] --]);
    if (rt == x) return ;
    h[x].pre = h[rt].pre;
    h[rt].pre = 0;
    while (h[x].fa)
    {
        int y = h[x].fa, z = h[y].fa;
        if (x == h[y].l)
        {
            if (y == h[z].l) zig(y);
            zig(x);
        }
        if (x == h[y].r)
        {
            if (y == h[z].r) zag(y);
            zag(x);
        }
    }
}

inline void Expose(int x)
{
    for (int y = 0; x; x = h[x].pre)
    {
        Splay(x);
        h[h[x].r].fa = 0;
        h[h[x].r].pre = x;
        h[x].r = y;
        h[y].fa = x;
        h[y].pre = 0;
        y = x;
    }
}

inline bool Connect(int u, int v)
{
    Expose(u);
    Splay(u);
    for (; h[v].fa || h[v].pre; v = h[v].fa ? h[v].fa : h[v].pre) ;
    return u == v;
}

inline void Make_Root(int x)
{
    Expose(x);
    Splay(x);
    h[x].flag ^= 1;
}

inline void Add(int u, int v)
{
    Make_Root(u);
    h[u].pre = v;
}

inline void Cut(int u, int v)
{
    Make_Root(u);
    Expose(v);
    Splay(v);
    h[h[v].l].fa = 0;
    h[v].l = 0;
}

int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        init();
        scanf("%d%d%d", &n, &m, &q);
        for (int i = 1; i <= m; i ++)
            scanf("%d%d", E[i], E[i] + 1);
        int i = 1, t = 1;
        while (t <= m)
        {
            if (i <= m && !Connect(E[i][0], E[i][1]))
                Add(E[i][0], E[i][1]), i ++;
            else
            {
                Max[t] = i;
                Cut(E[t][0], E[t][1]);
                t ++;
            }
        }
        int last=0;
        while (q --)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u=(u^last)%m+1;
            v=(v^last)%m+1;
            if (u>v) swap(u,v);
            if (v >= Max[u]) last=1,puts("Yes");
            else last=0,puts("No");
        }
    }
    return 0;
}
