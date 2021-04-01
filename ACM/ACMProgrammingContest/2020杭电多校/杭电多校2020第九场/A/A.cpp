#include<bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

template <typename T> bool chkmax(T &x,T y){return x<y?x=y,true:false;}
template <typename T> bool chkmin(T &x,T y){return x>y?x=y,true:false;}

int readint(){
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

int n,tot; ll ans=0;
int v[1000005],nxt[1000005],h[1000005],dep[1000005],siz[1000005];

void addedge(int x,int y){v[++tot]=y; nxt[tot]=h[x]; h[x]=tot;}

void dfs1(int u){
	siz[u]=1;
	for(int p=h[u];p;p=nxt[p]){
		dep[v[p]]=dep[u]+1;
		dfs1(v[p]);
		siz[u]+=siz[v[p]];
	}
}

void dfs2(int u,ll k){
	chkmax(ans,k);
	for(int p=h[u];p;p=nxt[p]) dfs2(v[p],k+n-siz[v[p]]);
}

int main(){
	int T=readint();
	while(T--){
		n=readint();
		for(int i=1;i<=n;i++) h[i]=0; tot=0;
		for(int i=2;i<=n;i++) addedge(readint(),i);
		ans=0;
		dep[1]=0; dfs1(1);
		dfs2(1,0);
		for(int i=1;i<=n;i++) ans+=siz[i];
		printf("%lld\n",ans);
	}
	return 0;
}
