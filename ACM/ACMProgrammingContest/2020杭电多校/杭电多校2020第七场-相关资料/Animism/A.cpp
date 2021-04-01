#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#define MAX 200005
using namespace std;
struct node {
    int l, r;
    node(int nl = 0, int nr = 0) {
        l = nl;
        r = nr;
    }
    bool operator<(const node& y) const { return r < y.r || (r == y.r && l < y.l); }
};
struct node2 {
    int l, r, dep;
    node2(int nl = 0, int nr = 0, int ndep = 0) {
        l = nl;
        r = nr;
        dep = ndep;
    }
    bool operator<(const node2& y) const 
    {
    	if(r!=y.r)return r<y.r;
		if(l!=y.l)return l<y.l;
		return dep<y.dep; 
	}
};
typedef set<node>::iterator I2;
typedef set<node2>::iterator I1;
const int inf = 1e9;
int tot = 0, dsu[MAX], fp[MAX], hd[MAX], pv[MAX];
int vis[MAX], n, m, x, y, jy[MAX], w, siz[MAX], seq[MAX],q;
int ans[MAX], zb[MAX], dep[MAX], zs[MAX];
vector<node> tk[MAX],oth[MAX];
vector<int> s[MAX];
set<node> st2[2][MAX];
set<node2> st[MAX];
vector<node> bt;
int getf(int p) { return dsu[p] == p ? p : dsu[p] = getf(dsu[p]); }
struct node3 {
    int x;
    node3(int nx = 0) { x = nx; }
    bool operator<(const node3& y) const {
        int fx = fp[getf(x)];
        int fy = fp[getf(y.x)];
        return fx < fy || (fx == fy && x < y.x);
    }
};
set<node3> stp[MAX];
typedef set<node3>::iterator I3;
void init()
{
	tot=0;
	for(int i=0;i<=2*q;i++)stp[i].clear(),ans[i]=dsu[i]=fp[i]=0;
	for(int i=1;i<=n;i++)st[i].clear(),st2[0][i].clear(),st2[1][i].clear(),s[i].clear(),tk[i].clear(),oth[i].clear();
	for(int i=1;i<=n;i++)
	{
		zb[i]=dep[i]=zs[i]=siz[i]=jy[i]=vis[i]=dsu[i]=hd[i]=0;
	}
}
void predfs(int p, int f) {
    int v;
    node h;
    vis[p] = siz[p] = 1;
    siz[p]+=(int)oth[p].size();
    dep[p] = dep[f] + 1;
    for(int i=0;i<oth[p].size();i++)
    {
    	h=oth[p][i];
    	if(!vis[h.l])continue;
    	v=getf(h.l);
    	if(h.r>q)tk[v].push_back(node(h.r-q,h.r));
    	else tk[v].push_back(node(h.r,h.r+q));
	}
    for (int i = 0; i < s[p].size(); i++) {
        v = s[p][i];
        if (v == f)
            continue;
        predfs(v, p);
        siz[p] += siz[v];
        if (siz[v] > siz[zs[p]])
            zs[p] = v;
    }
    dsu[p] = f;
}
node wah(node2 x, int p) {
    x.l += x.dep - dep[p];
    x.r -= x.dep - dep[p];
    return node(x.l, x.r);
}
void upd2(int pr, int p) {
    I3 it3;
    int r;
    r = fp[getf(pr)] - zb[p];
    while (!stp[pr].empty()) {
        it3 = stp[pr].begin();
        x = it3->x;
        y = fp[getf(x)] + zb[p];
        if (y <= r)
            ans[x-q] = 1, stp[pr].erase(it3), siz[pr]--;
        else
            break;
    }
}
void ins(int ty, node v, int p) {
    int res, fx;
    node u;
    I1 it;
    I2 it2;
    if (ty == 0)
        res = -zb[p];
    else
        res = zb[p];
    it = st[hd[p]].lower_bound(node2(-1, v.r, 0));
    if (it != st[hd[p]].end())
        u = wah(*it, p);
    else
        u.l = inf;
    if (u.l <= v.r && u.r >= v.r) {
        if (ty)
            v.r = u.l;
        else
            v.r = u.r;
    }
    st2[ty][hd[p]].insert(node(v.l, v.r - res));
    fp[v.l] = v.r - res;
    if (ty == 0 && siz[v.l])
        upd2(v.l, p);
}
void upd(int l, int r, int p) {
    node u;
    int x, y;
    I2 it2;
    I3 it3;
    bt.clear();
    while ((it2 = st2[1][hd[p]].lower_bound(node(-1, l - zb[p]))) != st2[1][hd[p]].end()) {
        u = *it2;
        if (u.r > r - zb[p])
            break;
        st2[1][hd[p]].erase(it2);
        bt.push_back(u);
    }
    if ((int)bt.size() > 0) {
        u = bt[0];
        fp[u.l] = l - zb[p];
        st2[1][hd[p]].insert(node(u.l, l - zb[p]));
        for (int i = 1; i < bt.size(); i++) dsu[bt[i].l] = u.l;
    }
    bt.clear();
    while ((it2 = st2[0][hd[p]].lower_bound(node(-1, l + zb[p]))) != st2[0][hd[p]].end()) {
        u = *it2;
        if (u.r > r + zb[p])
            break;
        st2[0][hd[p]].erase(it2);
        bt.push_back(u);
    }
    if ((int)bt.size() > 0) {
        for (int i = 1; i < bt.size(); i++)
            if (siz[bt[i].l] > siz[bt[0].l])
                swap(bt[0], bt[i]);
        u = bt[0];
        fp[u.l] = r + zb[p];
        st2[0][hd[p]].insert(node(u.l, r + zb[p]));
        for (int i = 1; i < bt.size(); i++) {
            dsu[bt[i].l] = u.l;
            siz[u.l] += siz[bt[i].l];
            for (it3 = stp[bt[i].l].begin(); it3 != stp[bt[i].l].end(); it3++) stp[u.l].insert(*it3);
        }
        upd2(u.l, p);
    }
}
void inse(node2 v, int p) {
    if (v.l >= v.r)
        return;
    node u;
    I1 it;
    int zl = v.l, zr = v.r;
    while ((it = st[hd[p]].lower_bound(node2(-1, zl, 0))) != st[hd[p]].end()) {
        if (it->l > v.r)
            break;
        u = wah(*it, p);
        st[hd[p]].erase(it);
        if (u.l >= u.r)
            continue;
        if (u.r < v.l || u.l > v.r)
            st[hd[p]].insert(node2(u.l, u.r, dep[p]));
        else
            v.l = min(v.l, u.l), v.r = max(v.r, u.r);
    }
    st[hd[p]].insert(v);
    upd(v.l, v.r, p);
}
void dfs(int p, int f) {
    I1 it;
    I2 it2;
    int v, fx, fy, tmp;
    node u;
    if (zs[p]) {
        dfs(zs[p], p);
        hd[p] = hd[zs[p]];
        zb[p] = zb[zs[p]] + 1;
        if (jy[p] > 0)
            inse(node2(0, jy[p], dep[p]), p);
    } else {
        hd[p] = ++tot;
        if (jy[p] > 0)
            st[hd[p]].insert(node2(0, jy[p], dep[p]));
    }
    for (int i = 0; i < s[p].size(); i++) {
        v = s[p][i];
        if (v == f || v == zs[p])
            continue;
        dfs(v, p);
        for (it = st[hd[v]].begin(); it != st[hd[v]].end(); it++) {
            u = wah(*it, p);
            inse(node2(u.l, u.r, dep[p]), p);
        }
        for (it2 = st2[1][hd[v]].begin(); it2 != st2[1][hd[v]].end(); it2++) {
            u = *it2;
            u.r += zb[v] + 1;
            ins(1, u, p);
        }
        for (it2 = st2[0][hd[v]].begin(); it2 != st2[0][hd[v]].end(); it2++) {
            u = *it2;
            u.r -= zb[v] + 1;
            ins(0, u, p);
        }
    }
    for(int i=0;i<oth[p].size();i++)
    {
    	u=oth[p][i];
    	if(u.r>q)ins(0,node(u.r-q,pv[u.r-q]),p);
    	else ins(1,node(u.r+q,0),p);
	}
    for (int i = 0; i < tk[p].size(); i++) {
        fx = fp[tmp = getf(tk[p][i].l)] - zb[p];
        fy = fp[getf(tk[p][i].r)] + zb[p];
        if (fx >= fy)
            ans[tk[p][i].l] = 1;
        else {
            siz[tmp]++;
            stp[tmp].insert(node3(tk[p][i].r));
        }
    }
}
int T;
int main() {
    	//freopen("1.in","r",stdin);
     //freopen("my.txt","w",stdout);
    scanf("%d",&T);
    while(T--)
    {
    	scanf("%d%d%d", &n, &m,&q);
    	for (int i = 1; i <= n; i++) dsu[i] = i;
    	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), s[x].push_back(y), s[y].push_back(x);
    	for (int i = 1; i <= q; i++)scanf("%d%d%d", &x, &y, &w), oth[x].push_back(node(y,q+i)), oth[y].push_back(node(x,i)), pv[i] = w, seq[i] =i;
    	for (int i = 1; i <= m; i++) scanf("%d%d", &x, &y), jy[x] = max(jy[x], y);
    	predfs(1, 0);
    	for (int i = 1; i <= 2*q; i++) dsu[i] = i, siz[i] = 0;
    	dfs(1, 0);
    	for (int i = 1; i <= q; i++) {
        	if (ans[seq[i]])
            	printf("YES\n");
        	else
            	printf("NO\n");
    	}
    	init();
    }
    return 0;
}
