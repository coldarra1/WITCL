#include<bits/stdc++.h>
#define rep(i,n) for(int i=1;i<=n;++i)
#define eb emplace_back
using namespace std;
constexpr int N=1e5+5,M=18,inf=1e9+7;
int T,n;
struct edge{
    int u,v,c;
}edg[N],trans[N];
int tmpb[N],tmpc[N];
bool cmp(edge x,edge y){return x.c<y.c;}
struct node_k{
    int c[2],sg[2],num,f[M];
};
struct res{
    int bl,br,cl,cr;
    int inibl,inibr,inicl,inicr;
    int mabl,mabr,macl,macr;
    bool chk(int bcur,int ccur){
        if(bcur<bl||br<bcur)return 0;
        if(ccur<cl||cr<ccur)return 0;
        if(
            (bcur<mabl||mabr<bcur||ccur<inicl||inicr<ccur)&&
            (ccur<macl||macr<ccur||bcur<inibl||inibr<bcur)
        )return 0;
        return 1;
    }
    bool fail(){
        if(bl>br)return 1;
        if(cl>cr)return 1;
        if((mabl>mabr||inicl>inicr)&&
            (macl>macr||inibl>inibr))
        return 1;
        return 0;
    }
}fky[N<<1];
int fa[N<<1],cnt;
struct kruskal_tree{
    node_k k[N<<1];
    int flt[N],rflt[N];
    int fae(int x){return fa[x]==x?x:fa[x]=fae(fa[x]);}
    void dfs(int x){
        if(k[x].c[0]==0){
            k[x].sg[0]=k[x].sg[1]=++cnt;
            flt[x]=cnt,rflt[cnt]=x;
            return;
        }
        dfs(k[x].c[0]),dfs(k[x].c[1]);
        k[x].sg[0]=k[k[x].c[0]].sg[0];
        k[x].sg[1]=k[k[x].c[1]].sg[1];
    }
    void build(edge e[N],int n,bool typ){
        rep(i,n<<1)fa[i]=i;
        rep(i,n)
            k[i].c[0]=k[i].c[1]=0,
            k[i].num=typ?0:inf;
        sort(e+1,e+n,cmp);
        if(!typ)reverse(e+1,e+n);
        rep(i,n-1){
            int x=fae(e[i].u),y=fae(e[i].v);
            fa[x]=fa[y]=n+i;
            k[x].f[0]=k[y].f[0]=n+i;
            k[n+i].c[0]=x,k[n+i].c[1]=y;
            k[n+i].num=e[i].c;
        }
        if(typ){
            k[n+n-1].f[0]=0;
            for(int i=n+n-1;i;--i)
                rep(j,M-1)k[i].f[j]=k[k[i].f[j-1]].f[j-1];
        }
        cnt=0;dfs(n+n-1);
    }
    int find(int x,int temp){
        for(int i=M-1;~i;--i)
            if(k[x].f[i]!=0&&k[k[x].f[i]].num<=temp)x=k[x].f[i];
        return x;
    }
    void sol(int x);
    int ck(int x,bool typ);
    void clr(int x,int hed);
}a;
struct node_p{
    int c[2],sum;
};
int tot;
struct persis_segtree{
    node_p p[N*M];
    int st[N];
    int add(int la,int l,int r,int num){
        int ret=++tot;
        if(l==r){
            p[ret].c[0]=p[ret].c[1]=0;
            p[ret].sum=1;
            return ret;
        }
        int mid=(l+r)>>1;
        if(num<=mid)
            p[ret].c[0]=add(p[la].c[0],l,mid,num),
            p[ret].c[1]=p[la].c[1];
        else
            p[ret].c[1]=add(p[la].c[1],mid+1,r,num),
            p[ret].c[0]=p[la].c[0];

        p[ret].sum=p[p[ret].c[0]].sum+p[p[ret].c[1]].sum;
        return ret;
    }
    void build(int a[N],int n){
        tot=0;
        rep(i,n)st[i]=add(st[i-1],1,n,a[i]);
    }
    int findsize(int tim0,int tim1,int l,int r,int x,int y){
        if(x<=l&&r<=y)return p[tim1].sum-p[tim0].sum;
        int ret=0,mid=(l+r)>>1;
        if(x<=mid)ret+=findsize(p[tim0].c[0],p[tim1].c[0],l,mid,x,y);
        if(mid+1<=y)ret+=findsize(p[tim0].c[1],p[tim1].c[1],mid+1,r,x,y);
        return ret;
    }
    int findmex(int tim0,int tim1,int l,int r,int x,int y){
        if(p[tim1].sum-p[tim0].sum==r-l+1)return -1;
        if(l==r)return l;
        int mid=(l+r)>>1;
        if(x<=mid){
            int tmp=findmex(p[tim0].c[0],p[tim1].c[0],l,mid,x,y);
            if(tmp!=-1)return tmp;
        }
        if(mid+1<=y){
            int tmp=findmex(p[tim0].c[1],p[tim1].c[1],mid+1,r,x,y);
            if(tmp!=-1)return tmp;
        }
        return -1;
    }
};

int tf[N];
struct atott{
    kruskal_tree Kt;
    persis_segtree Pt;
    void build(edge e[N],int n){
        Kt.build(e,n,1);
        rep(i,n)tf[i]=a.flt[Kt.rflt[i]];
        Pt.build(tf,n);
    }
    int fdsize(int top,int l,int r){
        return Pt.findsize(Pt.st[Kt.k[top].sg[0]-1],Pt.st[Kt.k[top].sg[1]],1,n,l,r);
    }
    int find(int top,int l,int r){
        return Pt.findmex(Pt.st[Kt.k[top].sg[0]-1],Pt.st[Kt.k[top].sg[1]],1,n,l,r);
    }
}b,c,ma;
vector<int>bg[N];
struct lcatree{
    int f[M][N],b[M][N],c[M][N],dep[N];
    void dfs(int x,int fa,edge e[N],int nb[N],int nc[N]){
        f[0][x]=(e[fa].u==x?e[fa].v:e[fa].u);
        dep[x]=dep[f[0][x]]+1;
        b[0][x]=(x==1?inf:nb[fa]);
        c[0][x]=(x==1?inf:nc[fa]);
        rep(i,M-1)
            f[i][x]=f[i-1][f[i-1][x]],
            c[i][x]=max(c[i-1][x],c[i-1][f[i-1][x]]),
            b[i][x]=max(b[i-1][x],b[i-1][f[i-1][x]]);
        for(int p:bg[x])if(p!=fa)
            dfs(e[p].u==x?e[p].v:e[p].u,p,e,nb,nc);
    }
    void build(edge e[N],int nb[N],int nc[N],int n){
        rep(i,n)bg[i].clear();
        rep(i,n-1)bg[e[i].u].eb(i),bg[e[i].v].eb(i);
        dfs(1,0,e,nb,nc);
    }
    int lca(int x,int y){
        if(dep[x]<dep[y])swap(x,y);
        for(int i=M-1;~i;--i)
            if(dep[f[i][x]]>=dep[y])x=f[i][x];
        if(x==y)return x;
        for(int i=M-1;~i;--i)
            if(f[i][x]!=f[i][y])x=f[i][x],y=f[i][y];
        return f[0][x];
    }
    int find(int posb,int posc,int temp){
        static int lc,x;
        lc=lca(posb,posc);
        x=posb;
        for(int i=M-1;~i;--i)
            if(dep[f[i][x]]>=dep[lc]&&b[i][x]<=temp)
                x=f[i][x];
        if(x!=lc)return x;
        x=posc;
        for(int i=M-1;~i;--i)
            if(dep[f[i][x]]>=dep[lc]&&c[i][x]<=temp)
                x=f[i][x];
        return x;
    }
}nd;

vector<int>ans;
bool flag;
int check(int topb,int topc,int l,int r,int temp){
    if(flag==0){
        memcpy(trans,edg,sizeof(trans[0])*n);
        rep(i,n-1)trans[i].c=max(tmpb[i],tmpc[i]);
        ma.build(trans,n);
        memcpy(trans,edg,sizeof(trans[0])*n);
        nd.build(trans,tmpb,tmpc,n);
        flag=1;
    }
    static int pos;
    pos=nd.find(b.Kt.rflt[b.Kt.k[topb].sg[0]],c.Kt.rflt[c.Kt.k[topc].sg[0]],temp);
    if(b.Kt.find(pos,temp)!=topb||c.Kt.find(pos,temp)!=topc)return -1;
    if(b.fdsize(topb,l,r)+c.fdsize(topc,l,r)-ma.fdsize(ma.Kt.find(pos,temp),l,r)==r-l+1)
        return pos;
    return -1;
}
#define cres fky[x]
#define ccs fky[k[x].c[typ]]
inline void upd(int&x,int&y,int u,int v){x=max(x,u),y=min(y,v);}
int kruskal_tree::ck(int x,bool typ){
    static int nda,topb,topc,eptb,eptc;
    nda=rflt[k[k[x].c[typ^1]].sg[0]];
    topb=b.Kt.find(nda,k[x].num),
    topc=c.Kt.find(nda,k[x].num);
    eptb=b.find(topb,k[k[x].c[typ^1]].sg[0],k[k[x].c[typ^1]].sg[1]),
    eptc=c.find(topc,k[k[x].c[typ^1]].sg[0],k[k[x].c[typ^1]].sg[1]);
    ccs=cres;
    if(eptb==-1&&eptc==-1){
            if(cres.inibl==0){
                upd(ccs.inibl,ccs.inibr,b.Kt.k[topb].sg[0],b.Kt.k[topb].sg[1]);
                upd(ccs.inicl,ccs.inicr,c.Kt.k[topc].sg[0],c.Kt.k[topc].sg[1]);
            }else{
                if(!(b.Kt.k[topb].sg[0]<=ccs.inibl&&ccs.inibr<=b.Kt.k[topb].sg[1]))
                    upd(ccs.macl,ccs.macr,c.Kt.k[topc].sg[0],c.Kt.k[topc].sg[1]);
                if(!(c.Kt.k[topc].sg[0]<=ccs.inicl&&ccs.inicr<=c.Kt.k[topc].sg[1]))
                    upd(ccs.mabl,ccs.mabr,b.Kt.k[topb].sg[0],b.Kt.k[topb].sg[1]);
            }
        return 1;
    }else if(eptb==-1){
        upd(ccs.bl,ccs.br,b.Kt.k[topb].sg[0],b.Kt.k[topb].sg[1]);
        return 1;
    }else if(eptc==-1){
        upd(ccs.cl,ccs.cr,c.Kt.k[topc].sg[0],c.Kt.k[topc].sg[1]);
        return 1;
    }else{
        static int tmp;
        int topeptc,topeptb;
        topeptc=c.Kt.find(rflt[eptb],k[x].num),topeptb=b.Kt.find(rflt[eptc],k[x].num);

        #define fk() \
        tmp=check(topb,topc,k[k[x].c[typ^1]].sg[0],k[k[x].c[typ^1]].sg[1],k[x].num); \
        if(tmp!=-1){ \
            upd(ccs.bl,ccs.br,b.Kt.k[topb].sg[0],b.Kt.k[topb].sg[1]); \
            upd(ccs.cl,ccs.cr,c.Kt.k[topc].sg[0],c.Kt.k[topc].sg[1]); \
            return 0; \
        }

        fk();
        int tp2=topc;topc=topeptc;
        fk();
        topc=tp2;topb=topeptb;
        fk();
    }
    return -1;
}
void kruskal_tree::clr(int x,int hed){
    if(k[x].c[0]==0){
        if(fky[hed].chk(b.Kt.flt[x],c.Kt.flt[x]))ans.eb(x);
        return;
    }
    clr(k[x].c[0],hed);clr(k[x].c[1],hed);
}
int tps[2][N<<1];
void kruskal_tree::sol(int x){
    if(k[x].c[0]==0){
        if(cres.chk(b.Kt.flt[x],c.Kt.flt[x]))ans.eb(x);
        return;
    }
    tps[0][x]=ck(x,0),tps[1][x]=ck(x,1);
    if(tps[0][x]>=0&&!fky[k[x].c[0]].fail()){
        if(tps[1][x]>0)clr(k[x].c[0],k[x].c[0]);
        else sol(k[x].c[0]);
    }
    if(tps[1][x]>=0&&!fky[k[x].c[1]].fail()){
        if(tps[0][x]>0)clr(k[x].c[1],k[x].c[1]);
        else sol(k[x].c[1]);
    }
}
int main(){

    for(scanf("%d",&T);T--;){
        scanf("%d",&n);
        rep(i,n-1)scanf("%d%d%d",&edg[i].u,&edg[i].v,&edg[i].c);
        memcpy(trans,edg,sizeof(trans[0])*n);
        a.build(trans,n,0);
        rep(i,n-1)scanf("%d%d%d%d",&edg[i].u,&edg[i].v,tmpb+i,tmpc+i);
        memcpy(trans,edg,sizeof(trans[0])*n);
        rep(i,n-1)trans[i].c=tmpb[i];
        b.build(trans,n);
        memcpy(trans,edg,sizeof(trans[0])*n);
        rep(i,n-1)trans[i].c=tmpc[i];
        c.build(trans,n);
        flag=0;

        ans.clear();
        fky[n+n-1]={1,n,1,n,0,n+1,0,n+1,1,n,1,n};
        a.sol(n+n-1);
        sort(ans.begin(),ans.end());
        if(ans.size()==0)puts("-1");
        else
            for(int i=0,mx=ans.size();i<mx;++i)
            printf("%d%c",ans[i]," \n"[i==mx-1]);
    }
}