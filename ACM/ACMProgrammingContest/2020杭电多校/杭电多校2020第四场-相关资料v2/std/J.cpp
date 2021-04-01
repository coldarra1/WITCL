#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pll pair<ll,ll>
#define fi first
#define se second


namespace Ohlover{
    int n, m;
    ll an2[202000], ans, bas, now;

    struct E{
        int lc, rc, l, r; ll v, laz;
    }e[1001000];
    int cne, qr[202000];
    priority_queue<pll,vector<pll>,greater<pll> >all;

    ll ggg[202000];

    int nnd(int l,int r,ll v){
        e[++cne]={0,0,l,r,v,0};
        return cne;
    }
    void PT(int x,ll v){
        e[x].laz+=v;
        e[x].v+=v;
    }
    void D(int x){
        if (!e[x].laz) return;
        if (e[x].lc) PT(e[x].lc,e[x].laz);
        if (e[x].rc) PT(e[x].rc,e[x].laz);
        e[x].laz=0;
    }
    int mgq(int x,int y){
        if (!x||!y) return x+y;
        if (e[x].v>e[y].v) swap(x,y);
        D(x);
        e[x].rc=mgq(e[x].rc,y);
        swap(e[x].lc,e[x].rc);
        return x;
    }

    int to[202000], fa[202000], pa[202000];
    int GF(int x){
        return x==fa[x]? x: fa[x]=GF(fa[x]);
    }
    int GP(int x){
        return x==pa[x]? x: pa[x]=GP(pa[x]);
    }

    struct TR{
        int lc, rc, sz;
    }tr[5001000]; int rt[202000], cntr;
    void ins(int &x,int l,int r,int p){
        if (!x) x=++cntr; tr[x]={0,0,0};
        ++tr[x].sz;
        if (l==r) return;
        int mid=l+r>>1;
        if (p<=mid) ins(tr[x].lc,l,mid,p);
        else ins(tr[x].rc,mid+1,r,p);
    }
    int quenex(int x,int l,int r,int p){
        if (tr[x].sz==r-l+1||r<p) return 0;
        if (l==r) return l;
        int mid=l+r>>1;
        int res=quenex(tr[x].lc,l,mid,p);
        if (res) return res;
        return quenex(tr[x].rc,mid+1,r,p);
    }
    void mgtr(int &x,int y,int l,int r){
        if (!y) return;
        if (!x){ x=y; return; }
        tr[x].sz+=tr[y].sz;
        int mid=l+r>>1;
        mgtr(tr[x].lc,tr[y].lc,l,mid);
        mgtr(tr[x].rc,tr[y].rc,mid+1,r);
    }

    void chk(int x){
        if (qr[x]) all.push({e[qr[x]].v+ggg[x],x});
    }

    void init(){
        memset(qr,0,sizeof qr); cne=0;
        memset(rt,0,sizeof rt); cntr=0;
        memset(ggg,0,sizeof ggg);
        while (!all.empty()) all.pop();
    }
    int main(){
        int k;
        cin>>n>>m>>k;
        for (;k--;){
            int x, l, r, c; scanf("%d %d %d %d",&x,&l,&r,&c);
            qr[x]=mgq(qr[x],nnd(l,r,-c));
        }
        for (int i=1;i<=n;++i){
            qr[i]=mgq(qr[i],nnd(1,n,0));
        }
        for (int i=1;i<=n;++i){
            ins(rt[i],1,n+1,i);
            to[i]=0; fa[i]=i; pa[i]=i;
            chk(i);
        }
        an2[now=n]=ans=-bas;
        while (all.size()&&all.top().fi<0){
            pll atp=all.top(); all.pop();
            int x=atp.se;
            int li=e[qr[x]].l, ri=e[qr[x]].r; ll vi=e[qr[x]].v;
            qr[x]=mgq(e[qr[x]].lc,e[qr[x]].rc);
            li=quenex(rt[x],1,n+1,li);
            if (li>ri){
                chk(x); continue;
            }
            ll y=li, w=vi; ++li; if (li<=ri) qr[x]=mgq(qr[x],nnd(li,ri,vi));
            y=GP(y);
            if (GF(y)==GF(x)){
                PT(qr[x],-w); ggg[x]+=w;
                int p=y; 
                while (p!=x){
                    p=GP(to[p]);
                    qr[y]=mgq(qr[y],qr[p]);
                    mgtr(rt[y],rt[p],1,n+1);
                    ggg[y]+=ggg[p];
                    pa[p]=y; fa[p]=y;
                }
                to[y]=0; fa[y]=y;
                chk(y);
            }else{
                ans+=ggg[x]+w; an2[--now]=ans;
                PT(qr[x],-w); ggg[x]=0; to[x]=y; fa[x]=GF(y);
            }
        }
        while (now>1) an2[--now]=ans;
        cout<<-an2[m]<<endl;
        return 0;
    }
}

int main(){
    int T;
    for (cin>>T;T--;){
        Ohlover::init();
        Ohlover::main();
    }
}