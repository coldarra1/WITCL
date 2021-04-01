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
VPII mas[SIZE];
struct Data{
    tuple<int,int,int>d;
    int id;
    int ty;
    Data(int x=0, int y=0, int z=0, int id=0, int ty=0):d(x,y,z), id(id), ty(ty){}
    bool operator<(const Data& b)const{
        return d > b.d || (d == b.d && ty < b.ty);
    }
}d[SIZE * 2];
int dn;
struct BIT{
    int _n;
    PII _d[SIZE];
    void init(int __n){
        _n=__n;
        FOR(i,1,_n)_d[i]={01,-1};
    }
    void ins(int x,PII v){
        for(;x<=_n;x+=x&-x)_d[x]=max(_d[x],v);
    }
    PII qq(int x){
        PII res={-1,-1};
        for(;x;x-=x&-x)res=max(_d[x],res);
        return res;
    }
}bit;
//TODO init
int n, Q;
VI e[SIZE];
// 0-based
#define MAX_LV 17
int jump[MAX_LV+1][SIZE],lv[SIZE];
void __init(int x,int lt){
    jump[0][x]=lt;
    REP(i,SZ(e[x])){
        int y=e[x][i];
        if(y!=lt){
            lv[y]=lv[x]+1;
            __init(y,x);
        }
    }
}
int adv(int x,int v){
    for(int i=0;(1<<i)<=v;i++){
        if((v>>i)&1)x=jump[i][x];
    }
    return x;
}
int lca(int x,int y){
    if(lv[x]>lv[y])x=adv(x,lv[x]-lv[y]);
    else y=adv(y,lv[y]-lv[x]);
    if(x==y)return x;
    for(int i=MAX_LV;i>=0;i--)
        if(jump[i][x]!=jump[i][y]){x=jump[i][x];y=jump[i][y];}
    return jump[0][x];
}
int dis(int x,int y){
    int z=lca(x,y);
    return lv[x]+lv[y]-lv[z]*2;
}
void build(int root,int N){
    __init(root,root);
    REPP(i,1,MAX_LV+1){
        REP(x,N)
            jump[i][x]=jump[i-1][jump[i-1][x]];
    }
}
PII dp[SIZE][3];
void update(PII to[], PII v){
    if(v > to[0]) {
        to[2] = to[1];
        to[1] = to[0];
        to[0] = v;
    }
    else if(v > to[1]) {
        to[2] = to[1];
        to[1] = v;
    }
    else if(v > to[2]) {
        to[2] = v;
    }
}
PII inc(PII x) {
    return {x.F+1,x.S};
}
void dfs0(int x,int lt) {
    dp[x][0] = {0, x};
    for(int y:e[x]){
        if(y == lt)continue;
        dfs0(y, x);
        update(dp[x], inc(dp[y][0]));
    }
}
void dfs2(int x,int lt, PII ma_from_up) {
    if(SZ(e[x]) > 1) {
        VPII tmp(dp[x],dp[x]+3);
        tmp.PB(ma_from_up);
        sort(ALL(tmp), greater<PII>());
        mas[x] = VPII(tmp.begin(), tmp.begin() + 3);
        d[dn++] = Data(tmp[2].F, tmp[1].F, tmp[0].F, x, 0);
    }
    for(int y: e[x]) {
        if(y == lt) continue;
        if(dp[y][0].S != dp[x][0].S) {
            dfs2(y, x, inc(max(ma_from_up, dp[x][0])));
        }
        else {
            dfs2(y, x, inc(max(ma_from_up, dp[x][1])));
        }
    }
}
int input[SIZE][3];
int an[SIZE][3];
int get_mid(int x, int y, int v){
    if(!v) return x;
    int z = lca(x, y);
    if(lv[x] - lv[z] >= v) {
        return adv(x, v);
    }
    return adv(y, lv[x] + lv[y] - lv[z] * 2 - v);
}
bool assign(int id,tuple<int, int, int> tpl,int center_id){
    VI res={get_mid(center_id, mas[center_id][0].S, get<2>(tpl)),
        get_mid(center_id, mas[center_id][1].S, get<1>(tpl)),
        get_mid(center_id, mas[center_id][2].S, get<0>(tpl)),
    };
    sort(ALL(res));
    do{
        if(dis(res[0], res[1]) == input[id][0] &&
           dis(res[0], res[2]) == input[id][1] &&
           dis(res[1], res[2]) == input[id][2]) {
            tie(an[id][0], an[id][1], an[id][2]) = make_tuple(res[0] ,res[1], res[2]);
            return 1;
        }
    }while(next_permutation(ALL(res)));
    return 0;
}
#include <sys/resource.h>
bool increase_stack_size( int size_mb ) {
    struct rlimit rl;
    if ( getrlimit(RLIMIT_STACK,&rl)!=0 ) return 0;
    rl.rlim_cur=size_mb*(1<<20);
    if ( rl.rlim_cur>rl.rlim_max ) rl.rlim_cur=rl.rlim_max;
    return setrlimit(RLIMIT_STACK,&rl)==0;
}
int main(){
    increase_stack_size(256);
    R(n);
    FOR(i,2,n){
        int x,y;
        R(x,y);
        e[x].PB(y);
        e[y].PB(x);
    }
    build(0,n);
    dfs0(0,0);
    dfs2(0,0,{-1,-1});
    R(Q);
    REP(i,Q){
        REP(j, 3) R(input[i][j]);
        if((input[i][0]+input[i][1]+input[i][2])%2){
            an[i][0]=-1;
            continue;
        }
        VI tmp{input[i][0]+input[i][1]-input[i][2],
               input[i][0]+input[i][2]-input[i][1],
               input[i][1]+input[i][2]-input[i][0]};
        sort(ALL(tmp));
        REP(j,3)tmp[j]/=2;
        if(tmp[0]<0){
            an[i][0]=-1;
        }
        else{
            d[dn++]=Data(tmp[0], tmp[1], tmp[2], i, 1);
        }
    }
    bit.init(n);
    sort(d, d + dn);
    REP(i, dn) {
        if(d[i].ty == 0) {
            bit.ins(n - get<1>(d[i].d),{get<2>(d[i].d), d[i].id});
        }
        else {
            PII ret = bit.qq(n - get<1>(d[i].d));
            if(ret.F >= get<2>(d[i].d)) {
                assert(assign(d[i].id, d[i].d, ret.S));
            }
            else an[d[i].id][0] = -1;
        }
    }
    REP(i, Q) {
        if(an[i][0] == -1) W(-1);
        else W(VI(an[i], an[i] + 3));
    }
    return 0;
}
