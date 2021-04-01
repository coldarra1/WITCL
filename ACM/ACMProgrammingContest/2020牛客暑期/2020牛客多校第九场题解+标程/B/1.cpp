#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define rep(i,a,b) for(reg int i=a,i##end=b;i<=i##end;++i)
#define drep(i,a,b) for(reg int i=a,i##end=b;i>=i##end;--i)
char IO;
int rd(){
	int s=0,f=0;
	while(!isdigit(IO=getchar())) if(IO=='-') f=1;
	do s=(s<<1)+(s<<3)+(IO^'0');
	while(isdigit(IO=getchar()));
	return f?-s:s;
}

const int N=1e5+10;
int n;
int a[N];
struct Edge{
	int to,nxt,w;
}e[N<<1];
int head[N],ecnt;
inline void AddEdge(int u,int v,int w){
	e[++ecnt]=(Edge){v,head[u],w};
	head[u]=ecnt;
}
struct Node1{
	ll a,b;
	inline bool operator < (const Node1 &__) const{
		return b>__.b;
	}
}A[N];//集合A
struct Node2{
	ll a,b;
	inline bool operator < (const Node2 &__) const{
		return a-b>__.a-__.b;
	}
}B[N];//集合B
int Ac,Bc;
ll dp[N],g[N]; //dp和g即上文论述的a，b
void dfs(int u,int f) {
	for(reg int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==f) continue;
		dfs(v,u);
		dp[v]-=2*e[i].w;//考虑这条边的影响
		g[v]-=e[i].w;
		g[v]=min(g[v],dp[v]);
		g[v]=min(g[v],(ll)-e[i].w);//先走边后吃草，所以考虑-w
	}
	Ac=Bc=0;
	for(reg int i=head[u];i;i=e[i].nxt) {
		int v=e[i].to;
		if(v==f) continue;
		if(dp[v]>=0) A[++Ac]=(Node1){dp[v],g[v]};
		else B[++Bc]=(Node2){dp[v],g[v]};
	}
	sort(A+1,A+Ac+1);
	sort(B+1,B+Bc+1);
	rep(i,1,Ac) {
		g[u]=min(g[u],dp[u]+A[i].b);
		dp[u]+=A[i].a;
	}
	rep(i,1,Bc) {
		g[u]=min(g[u],dp[u]+B[i].b);
		dp[u]+=B[i].a;
	} //模拟答案
	dp[u]+=a[u];
	g[u]+=a[u];//a[u]
}
int main(){
	n=rd();
	rep(i,1,n) a[i]=rd();
	rep(i,2,n) {
		int u=rd(),v=rd(),w=rd();
		AddEdge(u,v,w);
		AddEdge(v,u,w);
	}
	dfs(1,0);
	printf("%lld\n",max(0ll,-g[1]));
}
