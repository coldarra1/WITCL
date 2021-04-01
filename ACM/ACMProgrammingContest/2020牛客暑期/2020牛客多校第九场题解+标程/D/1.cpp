#include<bits/stdc++.h>
using namespace std;
const int N=100005;
int n,h[N],ans,l,r,w,nw,rs[N],k[N],cnt;
int f[N],len[N],s1[N],s2[N],tp[N],fa[N];
struct P{int x,y;}p[N];
struct E{int l,to;}e[N<<1];
vector<int>V[N<<2];
void Ad(int z,int y,int c){
    if(z>r||y<l)return;
    if(z>=l&&y<=r){
        V[c].push_back(w);
        return;
    }
    int mid=z+y>>1;
    if(l<=mid)Ad(z,mid,c<<1);
    if(r>mid)Ad(mid+1,y,c<<1|1);
}
void dfs(int x){
    cnt++;
    f[x]=tp[x]=x;
    s1[x]=s2[x]=len[x]=1;
    for(int i=h[x];i;i=e[i].l){
        int to=e[i].to;
        if(to==fa[x])continue;
        fa[to]=x;
        dfs(to);
        s2[x]++;
    }
}
int fi(int x){return x==f[x]? x:fi(f[x]);}
struct His{
    int f,sn,fx,s1,s2,len,tp,s2f;
}hs[N];
void Del(His a){
    f[a.sn]=a.sn;
    s2[a.fx]=a.s2f;
    s1[a.f]=a.s1;
    s2[a.f]=a.s2;
    len[a.f]=a.len;
    tp[a.f]=a.tp;
}
void Clr(int d){
    while(nw>d)Del(hs[nw--]);
}
void Qr(int z,int y,int c){
    int hl=nw;
    for(int i=V[c].size()-1;i>=0;i--){
        int x=p[V[c][i]].x,y=p[V[c][i]].y;
        if(fa[x]==y)swap(x,y);
        x=fi(x);y=fi(y);
        int fx=fi(fa[tp[x]]);
        if(len[x]<len[y]){
            hs[++nw]=(His){y,x,fx,s1[y],s2[y],len[y],tp[y],s2[fx]};
            f[x]=y;
            tp[y]=tp[x];
            s2[fx]+=s1[y];
            s2[y]=s2[x]+s2[y]-s1[y];
            s1[y]=s1[x]+s1[y];
        }else {
            hs[++nw]=(His){x,y,fx,s1[x],s2[x],len[x],tp[x],s2[fx]};
            f[y]=x;
            (len[x]==len[y])&&(len[x]++);
            s2[fx]+=s1[y];
            s2[x]=s2[x]+s2[y]-s1[y];
            s1[x]=s1[x]+s1[y];
        }
    }
    if(z==y){
        int x=fi(z),fx=fi(fa[tp[x]]);
        if(k[z])rs[z]=s2[x]+s1[fx];
        else rs[z]=s1[x];
        Clr(hl);
        return;
    }
    int mid=z+y>>1;
    Qr(z,mid,c<<1);Qr(mid+1,y,c<<1|1);
    Clr(hl);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)scanf("%d",&k[i]);
    for(int i=1;i<n;++i){
        scanf("%d %d %d %d",&p[i].x,&p[i].y,&l,&r);
        w=i;Ad(1,n,1);
        e[i<<1]=(E){h[p[i].y],p[i].x};h[p[i].y]=i<<1;
        e[i<<1|1]=(E){h[p[i].x],p[i].y};h[p[i].x]=i<<1|1;
    }
    dfs(1);
    Qr(1,n,1);
    for(int i=1;i<=n;++i)printf("%d\n",rs[i]);
    return 0;
}
