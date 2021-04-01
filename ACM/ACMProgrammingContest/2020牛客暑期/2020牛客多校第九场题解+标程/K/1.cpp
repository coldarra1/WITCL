#include<bits/stdc++.h>
#define N 100005
#define re register
#define ll long long
using namespace std;
int n,m,K;
inline void Rd(int &res){
	re char c;res=0;
	while(c=getchar(),c<48);
	do res=(res<<3)+(res<<1)+(c^48);
	while(c=getchar(),c>47);
}
int head[N],to[N<<1],nxt[N<<1],cnt1;
inline void add(int x,int y){to[++cnt1]=y;nxt[cnt1]=head[x];head[x]=cnt1;}
int T,fa[N],dep[N],V[N];
int Q[N],V1[N];
bool mk[N];
void dfs(int x,int f){
	fa[x]=f;dep[x]=dep[f]+1;
	V[x]=dep[x]>>1;
	for(re int i=head[x];i;i=nxt[i]){
		int y=to[i];
		if(y==f)continue;
		dfs(y,x);
	}
}
int main(){
//	freopen("escape.in","r",stdin);
	Rd(n);Rd(T);
	for(re int i=1;i<n;i++){
		int x,y;
		Rd(x),Rd(y);
		add(x,y);
		add(y,x);
	}
	dfs(n,0);
	int res=1;
	while(T--)res=fa[res];
	int l=0,r=1,ans=0;
	Q[1]=res;
	while(l<r){
		int x=Q[++l];
		if(mk[x])continue;
		mk[x]=1;
		if(V1[x]<=V[x])ans=max(ans,V[x]);
		if(V1[x]>=V[x])continue;
		for(re int i=head[x];i;i=nxt[i]){
			int y=to[i];
			if(mk[y])continue;
			V1[y]=V1[x]+1;
			Q[++r]=y;
		}
	}
	printf("%d\n",ans);
	return 0;
}
