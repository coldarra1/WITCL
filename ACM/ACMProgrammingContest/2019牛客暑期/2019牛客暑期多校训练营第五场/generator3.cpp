/*{{{*/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<string>
#include<iostream>
#include<sstream>
#include<set>
#include<map>
#include<queue>
#include<bitset>
#include<vector>
#include<limits.h>
#include<assert.h>
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define REP(I, N) for (int I = 0; I < (N); ++I)
#define REPP(I, A, B) for (int I = (A); I < (B); ++I)
#define FOR(I, A, B) for (int I = (A); I <= (B); ++I)
#define FORS(I, S) for (int I = 0; S[I]; ++I)
#define RS(X) scanf("%s", (X))
#define SORT_UNIQUE(c) (sort(c.begin(),c.end()), c.resize(distance(c.begin(),unique(c.begin(),c.end()))))
#define GET_POS(c,x) (lower_bound(c.begin(),c.end(),x)-c.begin())
#define CASET int ___T; scanf("%d", &___T); for(int cs=1;cs<=___T;cs++)
#define MP make_pair
#define PB push_back
#define MS0(X) memset((X), 0, sizeof((X)))
#define MS1(X) memset((X), -1, sizeof((X)))
#define LEN(X) strlen(X)
#define F first
#define S second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int,int> PII;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VPII;
typedef pair<LL,LL> PLL;
typedef vector<PLL> VPLL;
template<class T> void _R(T &x) { cin >> x; }
void _R(int &x) { scanf("%d", &x); }
void _R(LL &x) { scanf("%lld", &x); }
void _R(double &x) { scanf("%lf", &x); }
void _R(char &x) { scanf(" %c", &x); }
void _R(char *x) { scanf("%s", x); }
void R() {}
template<class T, class... U> void R(T &head, U &... tail) { _R(head); R(tail...); }
template<class T> void _W(const T &x) { cout << x; }
void _W(const int &x) { printf("%d", x); }
void _W(const LL &x) { printf("%lld", x); }
void _W(const double &x) { printf("%.16f", x); }
void _W(const char &x) { putchar(x); }
void _W(const char *x) { printf("%s", x); }
template<class T,class U> void _W(const pair<T,U> &x) {_W(x.F); putchar(' '); _W(x.S);}
template<class T> void _W(const vector<T> &x) { for (auto i = x.begin(); i != x.end(); _W(*i++)) if (i != x.cbegin()) putchar(' '); }
void W() {}
template<class T, class... U> void W(const T &head, const U &... tail) { _W(head); putchar(sizeof...(tail) ? ' ' : '\n'); W(tail...); }
#ifdef HOME
 #define DEBUG(...) {printf("# ");printf(__VA_ARGS__);puts("");}
#else
 #define DEBUG(...)
#endif
int MOD = 1e9+7;
void ADD(LL& x,LL v){x=(x+v)%MOD;if(x<0)x+=MOD;}
/*}}}*/
const int SIZE = 2e5+10;
struct CycleSequence {
    VI d0,d;
    void extend_st(int m) {
        if(m<=SZ(d0)) return;
        int it=0;
        while(SZ(d0)<m){
            d0.PB(d[it]);
            it++;
            if(it==SZ(d))it=0;
        }
        if(it) rotate(d.begin(),d.begin()+it,d.end());
    }
    int get_tail() { return SZ(d0);}
}xs, ys;
int pos[SIZE], gen_tmp[SIZE];
void gen(int x, int a, int b, int mod, CycleSequence& cs){
    REP(i,mod)pos[i] = -1;
    LL now = x;
    int id = 0;
    while(pos[now] == -1){
        gen_tmp[id] = now;
        pos[now] = id++;
        now = (now * a + b) % mod;
    }
    REP(i, pos[now]) cs.d0.PB(gen_tmp[i]);
    REPP(i, pos[now], id) cs.d.PB(gen_tmp[i]);
}
struct Point{
    LL x,y;
    int id;
    Point(int _x=0,int _y=0):x(_x),y(_y),id(-1){}
    LL operator*(const Point& b)const{return x*b.y-y*b.x;}
    Point operator-(const Point& b)const{
        return Point(x-b.x,y-b.y);
    }
    bool operator<(const Point& b)const{return MP(x,y)<MP(b.x,b.y);}
    void scan(){
        int _x,_y;
        R(_x,_y);
        x=_x;y=_y;
    }
    PLL get_pair(){
        return MP(x,y);
    }
}concerened_points[SIZE * 3];
int pn;
bool point_cmp(Point X,Point Y){
    LL v1=X.x*Y.y,v2=X.y*Y.x;
    if (v1==v2)return abs(X.x)+abs(X.y)<abs(Y.x)+abs(Y.y);
    return v1>v2;
}
LL convex_hull_area(Point _p[],int N){
    REPP(i,1,N){
        if(_p[i].get_pair()<_p[0].get_pair()){
            swap(_p[0],_p[i]);
        }
    } 
    Point O=_p[0];
    REP(i,N){_p[i].x-=O.x;_p[i].y-=O.y;}
    sort(_p+1,_p+N,point_cmp);
    vector<Point>ret;
    ret.PB(_p[0]);
    REPP(i,1,N){
        while(SZ(ret)>1&&(ret.back()-ret[SZ(ret)-2])*(_p[i]-ret[SZ(ret)-2])<=0)ret.pop_back();
        ret.PB(_p[i]);
    }
    if(SZ(ret) <= 2) return 0;
    LL ans = ret[0] * ret[SZ(ret)-1];
    REPP(i,1,SZ(ret)) ans += ret[i] * ret[i-1];
    return abs(ans);
}
template<class T>
T rmqfunc(T a, T b) {
    return MP(max(a.F,b.F),min(a.S,b.S));
}

template <class T,T RmqFunc(T,T)>
class RMQ{
    public:
        vector<int>log2;
        vector<vector<T>> values;

        template<class IterType> void build(IterType begin, IterType end){
            assert(begin!=end);
            int n=end-begin;
            log2=vector<int>(n+1);
            for(int i=2;i<=n;i++)log2[i]=log2[i>>1]+1;
            values=vector<vector<T> >(log2.back()+1,vector<T>(n));
            for(int i=0;i<n;i++){
                values[0][i]=*(begin+i);
            }
            for(int i=1;i<=log2.back();i++){
                int len=1<<i;
                int half_len=1<<(i-1);
                for(int j=0;j+len<=n;j++){
                    values[i][j]=RmqFunc(values[i-1][j], values[i-1][j+half_len]);
                }
            }
        }
        T query(int ll,int rr) {
            int len = rr-ll+1;
            int lv=log2[len];
            return RmqFunc(values[lv][ll], values[lv][rr-(1<<lv)+1]);
        }
};

void add_points(LL n,const VI& d1,const VI& d2) {
    if(n<=0)return;
    MS1(pos);
    VPII AA;
    REP(i,SZ(d1)){
        if(pos[i]!=-1)continue;
        for(int now=i;pos[now]==-1;now=(now+SZ(d2))%SZ(d1)) {
            pos[now] = SZ(AA);
            AA.PB({d1[now],d1[now]});
        }
    }
    int seg=SZ(d1)/__gcd(SZ(d1),SZ(d2));
    RMQ<PII,rmqfunc> rmq;
    rmq.build(ALL(AA));
    REP(i,SZ(d2)){
        if(i>=n)break;
        LL tt = (n-1-i) / SZ(d2) + 1;
        int me=pos[i%SZ(d1)];
        int ll=me/seg*seg;
        int rr=ll+seg-1;
        PII ret;
        if(tt>=seg) {
            ret = rmq.query(ll,rr);
        }
        else if(me+tt-1<=rr) {
            ret = rmq.query(me,me+tt-1);
        }
        else {
            ret = rmqfunc(rmq.query(me,rr), rmq.query(ll,ll+tt-(rr-me+1)-1));
        }
        concerened_points[pn++] = Point(ret.F, d2[i]);
        concerened_points[pn++] = Point(ret.S, d2[i]);
    }
}
int main(){
    int x0, y0, a_x, a_y, b_x, b_y, mod_x, mod_y;
    LL n;
    R(x0, y0, a_x, a_y, b_x, b_y, mod_x, mod_y, n);
    gen(x0, a_x, b_x, mod_x, xs);
    gen(y0, a_y, b_y, mod_y, ys);
    int tail_len=max(xs.get_tail(), ys.get_tail());
    xs.extend_st(tail_len);
    ys.extend_st(tail_len);
    add_points(n - tail_len, xs.d, ys.d);
    REP(i,min(n, (LL)tail_len)) {
        concerened_points[pn++] = Point(xs.d0[i],ys.d0[i]);
    }
    W(convex_hull_area(concerened_points, pn));
    return 0;
}
