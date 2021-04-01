#include<bits/stdc++.h>
#define N 200005
using namespace std;
int tot,last[N],to[N],Next[N],q[N],ans[N],st[N],en[N];
int dis[N],F[N],n,m,A[N],fa[N],si[N];
struct node {
	int s,v,d;
}f[N*4];
inline void add(int x,int y) {
	Next[++tot]=last[x]; last[x]=tot; to[tot]=y;
}
inline void dfs(int x,int y) {
	if (!y) y=x;
	F[x]=y;
	st[x]=++tot;
	A[tot]=x;
	int gt=0,gtw=0;
	for (int i=last[x];i;i=Next[i]) {
		if (si[to[i]]>gt) gt=si[gtw=to[i]];
	}
	if (gtw) dfs(gtw,y);
	for (int i=last[x];i;i=Next[i]) 
		if (to[i]!=gtw) dfs(to[i],0);
	en[x]=tot;
}
inline int Max(int x,int y) {
	if (!x||!y) return x+y;
	if (dis[x]>dis[y]) return x;
	return y;
}
inline void up(int x) {
	f[x].v=Max(f[x*2].v,f[x*2+1].v);
}
inline void build(int o,int l,int r) {
	if (l==r) {
		f[o].v=f[o].s=A[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(o*2,l,mid),build(o*2+1,mid+1,r);
	up(o);
	f[o].s=Max(f[o*2].s,f[o*2+1].s);
}
inline void change(int o,int l,int r,int ll,int rr,int p) {
	if (p&&f[o].d) return ;
	if (f[o].d) {
		if (l!=r) {		
			f[o*2].d=f[o*2+1].d=1;
			f[o*2].v=f[o*2].s;
			f[o*2+1].v=f[o*2+1].s;
		}
		f[o].d=0;
	}
	if (l==ll&&r==rr) {
		if (p) f[o].v=f[o].s,f[o].d=1;
		else f[o].v=0;
		return ;
	}
	
	int mid=(l+r)>>1;
	if (rr<=mid) change(o*2,l,mid,ll,rr,p);
	else if (ll>mid) change(o*2+1,mid+1,r,ll,rr,p);
	else change(o*2,l,mid,ll,mid,p),change(o*2+1,mid+1,r,mid+1,rr,p);
	up(o);
}
inline int find(int x,int k) {
	if (dis[x]<=k) return 1;
	while (1) {
		if (k<=dis[x]-dis[F[x]]) return A[st[x]-k];
		k-=(dis[x]-dis[F[x]]+1);
		x=fa[F[x]];
	}
}
inline int del(int x,int k) {
	int p=find(x,k);
	change(1,1,n,st[p],en[p],0);
	return p;
}
inline void ins(int x) {
	change(1,1,n,st[x],en[x],1);
}
inline int get(int k) {
	int r=0;
	while (1) {
		if (f[1].v==0) break;
		q[++r]=del(f[1].v,k);
	}
	for (int i=r;i;i--) ins(q[i]);
	return r;
}
int main() {
	while (scanf("%d",&n)!=EOF) {
		for (int i=1;i<=n;i++) si[i]=last[i]=0,ans[i]=n+1;
		tot=0;
		for (int i=2;i<=n;i++) {
			int x;
			scanf("%d",&x);
			assert(x<i);
			fa[i]=x;
			add(x,i);
			
		}
		for (int i=n;i;i--) si[i]++,si[fa[i]]+=si[i];
		for (int i=1;i<=n;i++) dis[i]=dis[fa[i]]+1;
		tot=0;
		dfs(1,0);
		build(1,1,n);
		for (int i=n;i>=0;i--) ans[get(i)]=i;
		for (int i=2;i<=n;i++) ans[i]=min(ans[i],ans[i-1]);
		long long Ans=0;
		for (int i=1;i<n;i++) Ans+=ans[i];
		printf("%lld\n",Ans);
	}
}
