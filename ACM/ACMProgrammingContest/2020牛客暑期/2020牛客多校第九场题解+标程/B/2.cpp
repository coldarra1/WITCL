#include <bits/stdc++.h>
using namespace std;
#define M 100005
template<class T>void tomin(T &x,T y){
	if(x>y)x=y;
}
typedef long long LL;
struct Edge{
	LL to,nx,w;
}edge[M<<1];
LL h[M],tt;
void link(LL a,LL b,LL w){
	edge[++tt].to=b;
	edge[tt].nx=h[a];
	edge[tt].w=w;
	h[a]=tt;
}
#define DEG(i,st) for(LL i=h[st];i;i=edge[i].nx)
LL n,V[M],E[M];
LL Val[M],f[M];
struct Node{
	LL a,b; 
	bool operator < (const Node &res)const{
		return a<res.a||a==res.a&&b>res.b;
	}
}A[M],B[M];
void dfs(LL F,LL now){
	Val[now]=V[now];
	DEG(i,now){
		LL to=edge[i].to;
		if(to==F)continue;
		E[to]=edge[i].w;
		dfs(now,to);
		Val[now]+=Val[to]-2LL*edge[i].w;
	}
	LL cta=0,ctb=0;
	DEG(i,now){
		LL to=edge[i].to;
		if(to==F)continue;
		LL mx=max(f[to]+E[to],(LL)E[to]+E[to]-Val[to]);
		if(Val[to]-E[to]-E[to]>=0)A[++cta]=(Node){mx,Val[to]-E[to]-E[to]};
		else B[++ctb]=(Node){mx+Val[to]-E[to]-E[to],-Val[to]+E[to]+E[to]};
	}
	sort(A+1,A+1+cta);
	sort(B+1,B+1+ctb);
	f[now]=0;
	LL mt=V[now];
	for(LL i=1;i<=cta;i++){
		if(mt<A[i].a)f[now]+=A[i].a-mt,mt=A[i].a;
		mt+=A[i].b;
	}
	for(LL i=1;i<=ctb;i++)mt-=B[i].b;
	for(LL i=1;i<=ctb;i++){
		if(mt<B[i].a)f[now]+=B[i].a-mt,mt=B[i].a;
		mt+=B[i].b;
	}
}
int main(){ 
	LL Cas;cin>>Cas;
	while(Cas--){
		memset(h,0,n+1<<3),tt=0;
		cin>>n;
		for(LL i=1;i<=n;i++){
			scanf("%lld",&V[i]);
		}
		for(LL i=1,a,b,w;i<n;i++){
			scanf("%lld%lld%lld",&a,&b,&w);
			link(a,b,w),link(b,a,w);
		}
		dfs(0,1);
		printf("%lld\n",f[1]);
	}
	return 0;
}
