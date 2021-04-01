//by Sshwy
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define FOR(i,a,b) for(int i=(a);i<=(b);++i)
#define ROF(i,a,b) for(int i=(a);i>=(b);--i)

namespace RA{
    int rnd(int p){return 1ll*rand()*rand()%p;}
    int rnd(int L,int R){return rnd(R-L+1)+L;}
}

int n,q;
const int SZ = 5e5+5;
template<class T>
struct Treap{
    int root,tot;
    int lc[SZ],rc[SZ],sz[SZ];
    unsigned int rnd[SZ];
    T val[SZ],mn[SZ];
    long long s[SZ];
    void clear(){
        fill(lc,lc+tot+1,0);
        fill(rc,rc+tot+1,0);
        fill(sz,sz+tot+1,0);
        root=tot=0;
    }
    Treap(){
        root=tot=0;
        srand(clock()+time(0));
        mn[0] = 1e9, s[0] = val[0] = 0;
    }
    inline void pushup(int u){
        sz[u] = sz[lc[u]]+sz[rc[u]]+1;
        mn[u] = min(val[u],min(mn[lc[u]],mn[rc[u]]));
        s[u] = s[lc[u]] + s[rc[u]] + val[u];
    }
    void split(int u,const int left_size,int &x,int &y){
        if(!u)return x=y=0,void();
        if(sz[lc[u]]+1<=left_size)x=u,split(rc[u],left_size-sz[lc[u]]-1,rc[u],y);
        else y=u,split(lc[u],left_size,x,lc[u]);
        pushup(u);
    }
    void split_by_min(int u,const int right_mn,int &x,int &y){
        if(!u)return x=y=0,void();
        if(mn[rc[u]] < right_mn || val[u] < right_mn) x=u,split_by_min(rc[u],right_mn,rc[u],y);
        else y=u,split_by_min(lc[u],right_mn,x,lc[u]);
        pushup(u);
    }
    int merge(int x,int y){//x<y
        if(!x||!y)return x+y;
        //if(rand()%(sz[x]+sz[y])<sz[x])return rc[x]=merge(rc[x],y), pushup(x), x;
        if(rnd[x]<rnd[y])return rc[x]=merge(rc[x],y), pushup(x), x;
        else return lc[y]=merge(x,lc[y]), pushup(y), y;
    }
    void insert(const int pos, const T v){ // 插入 v
        assert(pos);
        int x,y,u=++tot;
        s[u]=val[u]=mn[u]=v,sz[u]=1,rnd[u]=rand();
        split(root,pos-1,x,y);
        root = merge(merge(x,u),y);
    }
    int dfs(int * a,int l,int r){
        if(l>r)return 0;
        int u = ++tot, mid = (l+r)>>1;
        s[u]=val[u]=mn[u]=a[mid],sz[u]=r-l+1,rnd[u]=rand();
        lc[u] = dfs(a,l,mid-1);
        rc[u] = dfs(a,mid+1,r);
        pushup(u);
        return u;
    }
    void build_from(int * a,int l,int r){
        root = dfs(a,l,r);
    }
    void remove(const T v){
        int x,y,z;
        split_lower(root,v,x,y);
        split_upper(y,v,y,z);
        if(!y)assert(0); // 删除不存在的元素
        y=merge(lc[y],rc[y]);
        root=merge(x,merge(y,z));
    }
    int rank(T v){ // 即相同的数中，第一个数的排名
        int x,y,res;
        split_lower(root,v,x,y);
        res=sz[x]+1, root=merge(x,y);
        return res;
    }
    T kth(int k){ // 查询排名为 k 的数
        int u=root;
        while(k!=sz[lc[u]]+1){
            if(k<=sz[lc[u]])u=lc[u];
            else k-=sz[lc[u]]+1,u=rc[u];
        }
        return val[u];
    }
    void dfs_seq(int u,T * p){
        if(u==0)return;
        dfs_seq(lc[u],p);
        *(p+sz[lc[u]]+1) = val[u];
        dfs_seq(rc[u],p+sz[lc[u]]+1);
    }
    void seq(T * p){
        dfs_seq(root,p);
    }

    long long perform(int x,int y){
        if(kth(x)<y)return 0;
        int L,R;
        split(root,x,L,R);
        assert(L);

        if(mn[L]>=y){
            root = merge(L,R);
            return 0; // cant perform
        }
        int l,r;
        split_by_min(L,y,l,r);
        assert(l && r && mn[r]>=y);
        // l r R
        int l1,l2,r1,r2;
        long long res = s[r]-sz[r]*1ll*(y-1);
        split(l,sz[l]-1,l1,l2);
        split(r,1,r1,r2);
        assert(val[l2] < y);
        val[l2] += val[r1] - (y-1);
        s[l2] = mn[l2] = val[l2];
        s[r1] = mn[r1] = val[r1] = y-1;
        root = merge(merge(merge(l1,l2),merge(r2,r1)),R);
        assert(sz[root] == n);
        return res;
    }
};

Treap<int> T;

const int N=2e5+5;

int b[N];

void go(){
    scanf("%d%d",&n,&q);
    T.clear();
    FOR(i,1,n){
        scanf("%d",&b[i]);
    }
    T.build_from(b,1,n);
    FOR(i,1,q){
        int op,x,y;
        scanf("%d%d",&op,&x);
        if(op == 1)scanf("%d",&y),printf("%lld\n", T.perform(x,y));
        else printf("%d\n",T.kth(x));
    }
    T.seq(b);
    FOR(i,1,n)printf("%d%c",b[i]," \n"[i==n]);
}
int main(){
    int t;
    scanf("%d",&t);
    FOR(i,1,t)go();
    return 0;
}
