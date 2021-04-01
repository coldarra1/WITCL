#include<bits/stdc++.h>
using namespace std;
const int M=1e5+5;
const int Inf=0x3f3f3f3f;
const long long Infll=0x3f3f3f3f3f3f3f3f;

template<class T>bool tomax(T &x,T y){
	if(x<y)return x=y,1;
	return 0;
}
template<class T>bool tomin(T &x,T y){
	if(y<x)return x=y,1;
	return 0; 
}

int n,m,L[M],R[M],X[M],Y[M],U[M],V[M],S[M],T[M];

struct Edge{int v,to;}E[M<<1];int Head[M],e_tot=1;
void Link(int u,int v){E[++e_tot]=(Edge){v,Head[u]},Head[u]=e_tot;}

int Fa[M],Fe[M],dep[M],siz[M],son[M],tp[M],dfn[M],post[M],dti[M],dfnc;
long long dl[M];
void dfs_Init(int u)
{
    siz[u]=1;
    for(int i=Head[u];i;i=E[i].to)
    {
        int v=E[i].v;if(v==Fa[u])continue;
        Fa[v]=u;Fe[v]=i>>1;dep[v]=dep[u]+1;dl[v]=dl[u]+L[i>>1];
        dfs_Init(v);
        siz[u]+=siz[v];if(siz[v]>siz[son[u]])son[u]=v;
    }
}
void re_dfs_Init(int u)
{
    dti[dfn[u]=++dfnc]=u;
    if(son[u])tp[son[u]]=tp[u],re_dfs_Init(son[u]);
    for(int i=Head[u];i;i=E[i].to)
    {
        int v=E[i].v;if(v==Fa[u] || v==son[u])continue;
        tp[v]=v;
        re_dfs_Init(v);
    }
    post[u]=dfnc;
}
int LCA(int u,int v)
{
    while(tp[u]!=tp[v])
        if(dep[tp[u]]<dep[tp[v]])v=Fa[tp[v]];
        else u=Fa[tp[u]];
    return dep[u]<dep[v]?u:v;
}
int Dis(int u,int v){return dep[u]+dep[v]-dep[LCA(u,v)]*2;}
long long Dl(int u,int v){return dl[u]+dl[v]-dl[LCA(u,v)]*2;}
struct ST_Table
{
    int Log[M],Max[M][20];
    void Build()
    {
        for(int i=2;i<=n;i++)Log[i]=Log[i>>1]+1;
        for(int i=2;i<=n;i++)Max[i][0]=X[Fe[dti[i]]];
        for(int i=1;1+(1<<i)<=n;i++)
            for(int j=2;j+(1<<i)-1<=n;j++)
                Max[j][i]=max(Max[j][i-1],Max[j+(1<<(i-1))][i-1]);
    }
    int Query(int L,int R)
    {
        if(L>R)return 0;
        int b=Log[R-L+1];
        return max(Max[L][b],Max[R-(1<<b)+1][b]);
    }
}st;
long long Maxx(int u,int v)
{
    int ret=0;
    while(tp[u]!=tp[v])
        if(dep[tp[u]]<dep[tp[v]])ret=max(ret,st.Query(dfn[tp[v]],dfn[v])),v=Fa[tp[v]];
        else ret=max(ret,st.Query(dfn[tp[u]],dfn[u])),u=Fa[tp[u]];
    ret=max(ret,dep[u]<dep[v]?st.Query(dfn[u]+1,dfn[v]):st.Query(dfn[v]+1,dfn[u]));
    return ret;
}

int Root;
namespace KDT
{
	int son[M][2],ID[M],len,tt,fl;
	struct Node{
		int x,y,lx,rx,ly,ry;
		long long s,ad,ans,mxs;
		bool operator < (const Node &res)const{
			return fl?x<res.x:y<res.y;
		}
		void Reset(long long v,long long MXS,bool fl){
            tomin(ans,s+MXS),s+=v;
			if(fl){
				tomin(mxs,ad+MXS);
				ad+=v;
			}
		}
	}T[M];
	bool cmp(int a,int b){
		return T[a]<T[b];
	}
	void Up(int rt){
		T[rt].lx=T[rt].rx=T[rt].x;
		T[rt].ly=T[rt].ry=T[rt].y;
		for(int i=0;i<2;i++)if(son[rt][i]){
			tomax(T[rt].rx,T[son[rt][i]].rx);
			tomin(T[rt].lx,T[son[rt][i]].lx);
			tomax(T[rt].ry,T[son[rt][i]].ry);
			tomin(T[rt].ly,T[son[rt][i]].ly);
		}
	}
	
	int Build(int l,int r){
		if(l>r)return 0;
		int mid=(l+r)>>1;
		nth_element(ID+l,ID+mid,ID+1+r,cmp);
		int now=ID[mid];
		fl^=1;
		son[now][0]=Build(l,mid-1);
		son[now][1]=Build(mid+1,r);
		fl^=1;
		return Up(now),now;
	}
	
	void Down(int x){
		if(son[x][0])T[son[x][0]].Reset(T[x].ad,T[x].mxs, 1);
		if(son[x][1])T[son[x][1]].Reset(T[x].ad,T[x].mxs,1);
		T[x].ad=T[x].mxs=0;
	}
	
	void Update(int lx,int rx,int ly,int ry,long long v,int rt){
		if(!rt||lx>T[rt].rx||rx<T[rt].lx||ly>T[rt].ry||ry<T[rt].ly)return;
		if(lx<=T[rt].lx&&T[rt].rx<=rx&&ly<=T[rt].ly&&T[rt].ry<=ry)return void(T[rt].Reset(v,v,1)); 
        Down(rt);
		if(lx<=T[rt].x&&T[rt].x<=rx&&ly<=T[rt].y&&T[rt].y<=ry)T[rt].Reset(v,v,0);
		for(int i=0;i<2;i++)Update(lx,rx,ly,ry,v,son[rt][i]);
	}
	
	void Coll(int x,long long *Ans){
		if(!x)return;
		Ans[x]=T[x].ans;
		Down(x);
		for(int i=0;i<2;i++)Coll(son[x][i],Ans);
	}
};

struct event
{
    int e,t,val;
    bool operator <(const event &b)const{return t<b.t;}
}Ev[M<<1];
int Fir[M],Q[M],qpos;
bool cmp(int x,int y)
{
    if(Fir[x]!=Fir[y])return Fir[x]<Fir[y];
    else if(S[x]!=S[y])return S[x]<S[y];
    else return T[x]<T[y];
}
int evc;
void Make_Events()
{
    for(int i=1;i<n;i++)
    {
        if(X[i]>Y[i])swap(X[i],Y[i]),swap(L[i],R[i]);
        Ev[++evc]=(event){i,X[i],0};
        if(L[i]>R[i])Ev[++evc]=(event){i,Y[i],R[i]-L[i]};
    }
    sort(Ev+1,Ev+evc+1);
}
int Nowt;
void Execute(int id)
{
    int u=U[Ev[id].e],v=V[Ev[id].e];if(Fa[v]==u)swap(u,v);
    int t=Ev[id].t;
    if(t!=Nowt)
    {
        KDT::Update(1,n,1,n,t-Nowt,Root);
        Nowt=t;
        while(qpos<=m && Fir[Q[qpos]]<=t)
        {
            int q=Q[qpos];
            if(qpos==1 || (S[q]!=S[Q[qpos-1]] || T[q]!=T[Q[qpos-1]]))
                KDT::Update(dfn[S[q]],dfn[S[q]],dfn[T[q]],dfn[T[q]],-Infll,Root);
            qpos++;
        }
    }
    int val=Ev[id].val;
    if(val)
    {
        if(dfn[u]>1)KDT::Update(1,dfn[u]-1,dfn[u],post[u],val,Root);
        if(post[u]<n)KDT::Update(dfn[u],post[u],post[u]+1,n,val,Root);
    }
}

long long Ans[M];
void Solve()
{
    Make_Events();
    dfs_Init(1);re_dfs_Init(1);st.Build();
    for(int i=1;i<=m;i++)if(dfn[S[i]]>dfn[T[i]])swap(S[i],T[i]);
    for(int i=1;i<=m;i++){
        Fir[i]=Maxx(S[i],T[i]);
        long long Val=Dl(S[i],T[i])+Infll;
        KDT::T[i].x=dfn[S[i]],KDT::T[i].y=dfn[T[i]],KDT::ID[i]=i;
        KDT::T[i].ans=KDT::T[i].s=Val;
        KDT::T[i].ad=KDT::T[i].mxs=0;
    }
    Root=KDT::Build(1,m);
    for(int i=1;i<=m;i++)Q[i]=i;sort(Q+1,Q+m+1,cmp);qpos=1;
    for(int i=1;i<=evc;i++)Execute(i);
    KDT::Coll(Root,Ans);
    for(int i=1;i<=m;i++)printf("%lld\n",S[i]==T[i]?0:Ans[i]);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%d%d%d%d",&U[i],&V[i],&L[i],&R[i],&X[i],&Y[i]);
        Link(U[i],V[i]);Link(V[i],U[i]);
    }
    for(int i=1;i<=m;i++)scanf("%d%d",&S[i],&T[i]);
    Solve();
    return 0;
}
