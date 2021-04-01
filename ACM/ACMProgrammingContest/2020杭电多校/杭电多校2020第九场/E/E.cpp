#include<bits/stdc++.h>
#define ci const int&
using namespace std;
const int mod=1e9+7;
struct edge{
	int t,nxt;
}e[800010];
int T,n,m,u,v,cnt,be[200010],dfn[200010],low[200010],sz,q[200010],qs,siz[200010],ts,sum[3][200010],ans,ta;
vector<int>ar;
int POW(int x,int y){
	x>mod?x-=mod:0;
	int ret=1;
	while(y)y&1?ret=1ll*ret*x%mod:0,x=1ll*x*x%mod,y>>=1;
	return ret;
}
void add(ci x,ci y){
	e[++cnt]=(edge){y,be[x]},be[x]=cnt;
}
void Calc(){
	ts=ar.size()-1,ta=0;
	if(ts==2)return(void)(ans=(ans+1ll*ar[1]*ar[2])%mod);
	for(int i=1;i<ar.size();++i){
		sum[0][i]=(sum[0][i-1]+ar[i])%mod;
		sum[1][i]=(sum[1][i-1]+1ll*ar[i]*i)%mod;
		sum[2][i]=(sum[2][i-1]+1ll*ar[i]*i*i)%mod;
		ta=(ta+1ll*ar[i]*(((1ll*ts*i-1ll*i*i)%mod*sum[0][i]+1ll*((i<<1)-ts)*sum[1][i]-sum[2][i])%mod+mod))%mod;
	}
	ans=(ans+1ll*ta*POW(ts,mod-2))%mod;
}
void dfs(ci x){
	dfn[x]=low[x]=++sz,siz[x]=1,q[++qs]=x;
	for(int i=be[x];i;i=e[i].nxt)if(!dfn[e[i].t]){
		dfs(e[i].t),low[x]=min(low[x],low[e[i].t]);
		if(low[e[i].t]>=dfn[x]){
			ar.resize(1),ts=n;
			while(qs>0&&q[qs]!=e[i].t)ts-=siz[q[qs]],siz[x]+=siz[q[qs]],ar.push_back(siz[q[qs--]]);
			ts-=siz[q[qs]],siz[x]+=siz[q[qs]],ar.push_back(siz[q[qs--]]),ar.push_back(ts),Calc();
		}
	}else low[x]=min(low[x],dfn[e[i].t]);
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m),ans=0,cnt=sz=qs=0;
		for(int i=1;i<=n;++i)be[i]=dfn[i]=0;
		for(int i=1;i<=m;++i)scanf("%d%d",&u,&v),add(u,v),add(v,u);
		dfs(1);
		printf("%d\n",ans);
	}
	return 0;
}
/*
3

4 4
1 2
1 3
2 3
1 4

15 18
1 2
1 3
2 3
2 8
2 9
8 9
2 10
2 11
10 12
11 13
12 13
13 14
14 15
3 4
4 5
4 6
5 7
6 7

5 6
1 2
1 3
2 3
2 4
2 5
4 5
*/
