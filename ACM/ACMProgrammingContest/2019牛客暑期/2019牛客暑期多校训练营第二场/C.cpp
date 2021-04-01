// {{{ by WangYenJen
#include <bits/stdc++.h>

using namespace std;

// types
typedef long long ll;
typedef pair<int,int> pii;

// macro
#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin() , (x).end()
#define REP(i , n) for(int i = 0; i < int(n); i++)
#define REP1(i , a , b) for(int i = a; i <= int(b); i++)
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define LC o<<1 , l , m
#define RC o<<1|1 , m + 1 , r
#define MS(x , v) memset(x , (v) , sizeof(x))

// input
inline bool SR(int &x) {
	return scanf("%d",&x) == 1;
}
inline bool SR(ll &x) {
	return scanf("%lld",&x) == 1;
}
inline bool SR(double &x) {
	return scanf("%lf",&x) == 1;
}
inline bool SR(char *s) {
	return scanf("%s",s) == 1;
}
inline bool RI() {
	return true;
}
template<typename I , typename... T> inline bool RI(I &x , T&... tail) {
	return SR(x) && RI(tail...);
}

// output
inline void SP(const int x) {
	printf("%d",x);
}
inline void SP(const ll x) {
	printf("%lld",x);
}
inline void SP(const double x) {
	printf("%.16lf",x);
}
inline void SP(const char *s) {
	printf("%s",s);
}
inline void PL() {
	puts("");
}
template<typename I , typename... T> inline void PL(const I x , const T... tail) {
	SP(x);
	if(sizeof...(tail)) putchar(' ');
	PL(tail...);
}

// debug
#define WangYenJen
#ifdef WangYenJen
template<typename I> void _DOING(const char *s , I&& x) {
    cerr << s << " = " << x << endl;
}
template<typename I , typename... T> void _DOING(const char *s , I&& x , T&&... tail) {
    int c = 0;
    while(*s != ',' || c != 0) {
        if(*s == '(' || *s == '[' || *s == '{') c++;
        if(*s == ')' || *s == ']' || *s == '}') c--;
        cerr << *s++;
    }
    cerr << " = " << x << " , ";
    _DOING(s + 1 , tail...);
}
#define debug(...) \
do {\
    fprintf(stderr , "%s:%d - ",__PRETTY_FUNCTION__,__LINE__);\
    _DOING(#__VA_ARGS__ , __VA_ARGS__);\
} while(0);
#else
#define debug(...)
#endif

// random function
inline int RAND() {
	static int x = 880301;
	return (x = x * 0xdefaced + 1) % 0x7fffffff;
}
// }}}

const int INF = 0x3f3f3f3f;
const int MAX_N = 1000000 + 7;

#undef ALL

/* ---------------------------------Splay 1----------------------------------------- */
#define rep(i,x,y) for(i=x;i<=y;i++)
#define _rep(i,x,y) for(i=x;i>=y;i--)
#define ALL(x,S) for(x=S.begin();x!=S.end();x++)
#define mp make_pair
#define fi first
#define se second
#define pb push_back
template<class T> inline void read(T&x){bool fu=0;char c;for(c=getchar();c<=32;c=getchar()){}if(c=='-')fu=1,c=getchar();for(x=0;c>32;c=getchar())x=x*10+c-'0';if(fu)x=-x;};
template<class T> inline void read(T&x,T&y){read(x);read(y);}
template<class T> inline void read(T&x,T&y,T&z){read(x);read(y);read(z);}
inline char getc(){char c;for(c=getchar();c<=32;c=getchar()){}return c;}

int max(int a,int b,int c){return max(max(a,b),c);}

const int inf=int(1e9);
int n,m,i,j,k,x,y,u,v,w0,w1;

multiset<int> son[MAX_N],AMAX_N;
multiset<int>::iterator pos;

priority_queue<pii> Q;

int ch[MAX_N][2],fa[MAX_N],key[MAX_N];bool rev[MAX_N];
int lw[MAX_N],rw[MAX_N],ans2[MAX_N],len[MAX_N];

void Hins(int i,int t){son[i].insert(lw[t]);}
void Hdel(int i,int t){son[i].erase(son[i].find(lw[t]));}
int mson(int i){return son[i].empty()?0:*son[i].rbegin();}
int tson(int i){if(son[i].size()<=1)return mson(i);pos=--son[i].end();return *pos+*(--pos);}

bool tp(int i){return !(ch[fa[i]][0]==i||ch[fa[i]][1]==i);}
void REV(int i){if(i){rev[i]=!rev[i];swap(ch[i][0],ch[i][1]);swap(lw[i],rw[i]);}}
void D(int i){if(rev[i])rev[i]=0,REV(ch[i][0]),REV(ch[i][1]);}
void U(int i)
{
    #define L ch[i][0]
    #define R ch[i][1]
    len[i]=len[L]+key[i]+len[R];
    ans2[i]=max(rw[L]+lw[R],max(rw[L],lw[R])+mson(i),tson(i))+key[i];
    lw[i]=max(lw[L],len[L]+key[i]+mson(i),len[L]+key[i]+lw[R]);
    rw[i]=max(rw[R],len[R]+key[i]+mson(i),len[R]+key[i]+rw[L]);
    Q.push(mp(ans2[i],i));
}

void rot(int i,int t){int x,y;x=ch[i][!t];D(x);y=ch[x][t];ch[i][!t]=y;ch[x][t]=i;if(y)fa[y]=i;if(fa[i])if(ch[fa[i]][0]==i)ch[fa[i]][0]=x;else if(ch[fa[i]][1]==i)ch[fa[i]][1]=x;fa[x]=fa[i];fa[i]=x;U(i);}
void spl(int x){int y,z;D(x);while(!tp(x)){y=fa[x];z=fa[y];if(z)D(z);if(y)D(y);if(tp(y))rot(y,ch[y][0]==x);else if(ch[z][0]==y)if(ch[y][0]==x)rot(z,1),rot(y,1);else rot(y,0),rot(z,1);else if(ch[y][0]==x)rot(y,1),rot(z,0);else rot(z,0),rot(y,0);U(x);}}
void acc(int x){for(int i=0,t;x;i=x,x=fa[x]){spl(x);t=ch[x][1];if(t)Hins(x,t);ch[x][1]=i;if(i){fa[i]=x;Hdel(x,i);}U(x);}}
void maker(int x){acc(x);spl(x);REV(x);}
void change(int x,int y){acc(x);spl(x);key[x]=y;U(x);}
void cut(int x,int y){maker(x);acc(y);spl(y);ch[y][0]=0;fa[x]=0;U(y);}
void link(int x,int y){maker(x);acc(y);spl(y);fa[x]=y;Hins(y,x);U(y);}
vector<int> E[MAX_N];void dfs(int i){vector<int>::iterator it;ALL(it,E[i])if((*it)!=fa[i])fa[*it]=i,dfs(*it),Hins(i,*it);U(i);}
int solve(){pii u;while(1){u=Q.top();if(ans2[u.se]==u.fi)break;Q.pop();}return u.fi;}
/* --------------------------------------------------------------------------------- */

/* ---------------------------------Splay 2----------------------------------------- */
struct Node {
    static Node mem[MAX_N] , *pmem;
    Node *par , *ch[2] , *mx;
    int id , sz , rev_tag , val, mx_len, dp;

    Node(int _id = 0 , int _val = 0) : par(0) , id(_id) , sz(1) , rev_tag(0) , mx(this) , val(_val), mx_len(0), dp(0) {
        MS(ch , 0);
    }
} Node::mem[MAX_N] , *Node::pmem = Node::mem;

int N;
Node *tr[MAX_N];

inline void rev2(Node *o) {
    swap(o->ch[0] , o->ch[1]);
    o->rev_tag ^= 1;
}

inline int sz(Node *o) {
    return o ? o->sz : 0;
}

inline void push(Node *o) {
    if(o->rev_tag) {
        REP(i , 2) if(o->ch[i]) rev2(o->ch[i]);
        o->rev_tag ^= 1;
    }
}

inline void pull(Node *o) {
    o->sz = sz(o->ch[0]) + 1 + sz(o->ch[1]);
    o->mx = o;
    REP(i , 2) if(o->ch[i] && o->ch[i]->mx->val > o->mx->val) o->mx = o->ch[i]->mx;
}

inline int get_ch_id(Node *p , Node *o) {
    REP(i , 2) if(p->ch[i] == o) return i;
    return -1;
}

inline void rotate(Node *o , int d) {
    push(o);
    push(o->ch[d]);
    Node *u = o;
    o = o->ch[d];
    Node *p = u->par;
    int t;
    if(p && (t = get_ch_id(p , u)) != -1) p->ch[t] = o;
    o->par = p;
    u->par = o;
    if(o->ch[d^1]) o->ch[d^1]->par = u;
    u->ch[d] = o->ch[d^1];
    o->ch[d^1] = u;
    pull(u);
    pull(o);
}

inline void rotate(Node *o) {
    if(sz(o->ch[0]) > sz(o->ch[1])) rotate(o , 0);
    else if(sz(o->ch[0]) < sz(o->ch[1])) rotate(o , 1);
}

inline void all_push(Node *o) {
    if(o->par && get_ch_id(o->par , o) != -1) all_push(o->par);
    push(o);
}

inline void splay(Node *o) {
    all_push(o);
    Node *p;
    for(int d; (p = o->par) && (d = get_ch_id(p , o)) != -1;) {
        rotate(p , d);
        rotate(p);
    }
}

inline Node* access(Node *o) {
    Node *last = 0;
    while(o) {
        splay(o);
        o->ch[1] = last;
        pull(o);
        last = o;
        o = o->par;
    }
    return last;
}

inline void make_root(Node *o) {
    rev2(access(o));
    splay(o);
}

inline void link(Node *a , Node *b) {
    make_root(b);
    b->par = a;
}

inline void cut(Node *a , Node *b) {
    make_root(a);
    access(b);
    splay(b);
    b->ch[0] = 0;
    a->par = 0;
    pull(b);
}

inline Node* find_root(Node *o) {
    o = access(o);
    while(o->ch[0]) o = o->ch[0];
    splay(o);
    return o;
}

vector<tuple<int, int, int> > rds;
vector<tuple<int, int, int> > rds2;

vector<tuple<int, int, int> > es;

inline pair<int, int> add_edge(int i , int x , int y , int v) {
    int cnt2 = 0;
    if(find_root(tr[x]) == find_root(tr[y])) {
        make_root(tr[x]);
        access(tr[y]);
        splay(tr[x]);
        int id = tr[x]->mx->id - N;
        if(get<2>(es[id]) > v) {
            cut(tr[get<0>(es[id])] , tr[N + id]);
            cut(tr[get<1>(es[id])] , tr[N + id]);
            link(tr[x] , tr[N + i]);
            link(tr[y] , tr[N + i]);
            rds.emplace_back(1, get<0>(es[id]), N + id);
            rds.emplace_back(1, get<1>(es[id]), N + id);
            rds.emplace_back(0, x, N + i);
            rds.emplace_back(0, y, N + i);

            cut(get<0>(es[id]) + 1, get<1>(es[id]) + 1);
            link(x + 1, y + 1);
            solve();
            rds2.emplace_back(1, get<0>(es[id]) + 1, get<1>(es[id]) + 1);
            rds2.emplace_back(0, x + 1, y + 1);
            return make_pair(4, 2);
        }
        return make_pair(0, 0);
    }
    else {
        assert(0);
        link(tr[x] , tr[N + i]);
        link(tr[y] , tr[N + i]);
        rds.emplace_back(0, x, N + i);
        rds.emplace_back(0, y, N + i);

        link(x + 1, y + 1);
        rds2.emplace_back(0, x + 1, y + 1);

        return make_pair(2, 1);
    }
}


/* --------------------------------------------------------------------------------- */

struct Dsu {
    int cnt;
    stack<pair<int*,int> > stk_sz;
    stack<pair<int*,int> > stk_par;
    int par[MAX_N] , sz[MAX_N];
 
    void init(int n) {
        while(!stk_sz.empty()) stk_sz.pop();
        while(!stk_par.empty()) stk_par.pop();
        cnt = n;
        for (int i = 0; i < n; i++) {
            par[i] = i;
            sz[i] = 1;
        }
    }
 
    int find(int x) {
        if(par[x] == x) return x;
        else return find(par[x]);
    }
 
    bool merge(int x , int y) {
        x = find(x);
        y = find(y);
        if(x == y) return 0;
        if(sz[x] < sz[y]) swap(x , y);
        stk_sz.push(make_pair(&sz[x] , sz[x]));
        stk_par.push(make_pair(&par[y] , par[y]));
        sz[x] += sz[y];
        par[y] = x;
        cnt--;
        return 1;
    }
 
    bool query(int x , int y) {
        return find(x) == find(y);
    }
 
    bool undo() {
        if(stk_sz.empty()) return 0;
        pair<int*,int> p_sz = stk_sz.top();
        pair<int*,int> p_par = stk_par.top();
        stk_sz.pop();
        stk_par.pop();
        *p_sz.first = p_sz.second;
        *p_par.first = p_par.second;
        cnt++;
        return 1;
    }
} dsu;
 
ll ans[MAX_N];
vector<tuple<int, int, int, int> > seg[MAX_N<<2];

void insert(int o , int l , int r , int ql , int qr , tuple<int, int, int, int> e) {
    if(ql <= l && r <= qr) {
        seg[o].push_back(e);
        return;
    }
    int m = (l + r) >> 1;
    if(ql <= m) insert(o<<1, l, m , ql , qr , e);
    if(m < qr) insert(o<<1|1, m + 1, r , ql , qr , e);
}
 
void dfs(int o , int l , int r) {
    int cnt = 0;
    int cnt2 = 0;
    int cnt3 = 0;
    for (int i = 0; i < (int)seg[o].size(); i++) {
        int id, a, b, c;
        tie(id, a, b, c) = seg[o][i];
        auto p = add_edge(id, a, b, c);
        cnt += p.first;
        cnt2 += p.second;
        if (dsu.merge(a, b))
            cnt3++;
    }
    if(l != r) {
        int m = (l + r) >> 1;
        dfs(o<<1, l, m);
        dfs(o<<1|1, m + 1, r);
    }
    else {
        if (dsu.cnt != 1) ans[l] = -1;
        else ans[l] = solve() - 1;
    }
    while(cnt--) {
        int op, a, b;
        tie(op, a, b) = rds.back();
        rds.pop_back();
        if (op == 0)
            cut(tr[a], tr[b]);
        else
            link(tr[a], tr[b]);
    }
    for (int i = 0; i < cnt2; i++) {
        int op, a, b;
        tie(op, a, b) = rds2.back();
        rds2.pop_back();
        if (op == 0)
            cut(a, b);
        else
            link(a, b);
        if (i % 2)
            solve();
    }
    while (cnt3--) dsu.undo();
}

map<tuple<int, int, int>, vector<int> > mps;

int main() {
    for (int i = 0; i < MAX_N; i++)
        key[i] = 1;
    int Q;
    scanf("%d%d", &N, &Q);
    dsu.init(N);
    REP(i , N) tr[i] = new (Node::pmem++)Node(i);
    for (int i = N + Q; i < N + Q + N - 1; i++)
        tr[i] = new (Node::pmem++)Node(i, INF);
    for (int i = 0; i < N - 1; i++) {
        link(tr[i], tr[N + Q + i]);
        link(tr[i + 1], tr[N + Q + i]);

        E[i + 1].push_back(i + 2);
        E[i + 2].push_back(i + 1);
    }
    dfs(1);
    solve();
    REP(i, Q) {
        int op, a, b, c;
        scanf("%d%d%d%d", &op, &a, &b, &c);
        tr[N + i] = new (Node::pmem++)Node(N + i , c);
        a--, b--;
        es.emplace_back(a, b, c);
        if (op == 1) {
            mps[make_tuple(a, b, c)].push_back(i);
        }
        else {
            if (mps[make_tuple(a, b, c)].size()) {
                insert(1, 0,  Q - 1, mps[make_tuple(a, b, c)].back(), i - 1, make_tuple(mps[make_tuple(a, b, c)].back(), a, b, c));
                mps[make_tuple(a, b, c)].pop_back();
            }
        }
    }
    for (int i = 0; i < N - 1; i++)
        es.emplace_back(i, i + 1, INF);
    for (auto it : mps) {
        tuple<int, int, int> t = it.first;
        int a, b, c;
        tie(a, b, c) = t;
        for (int y : it.second)
            insert(1, 0, Q - 1, y, Q - 1, make_tuple(y, a, b, c));
    }
    dfs(1, 0, Q - 1);
    REP(i, Q)
        printf("%lld\n", ans[i]);
    return 0;
}
