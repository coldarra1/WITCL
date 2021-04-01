#include <bits/stdc++.h>
using namespace std;
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define SZ 666666
int n,k,b[SZ],ls=0,vis[SZ],d[SZ]; Edg
void bfs(int s,int c)
{
	queue<int> q; d[s]=0;
	vis[s]=c; q.push(s);
	while(!q.empty())
	{
		int x=q.front(); q.pop();
		if(b[x]) ls=x;
		for esb(x,e,t) if(vis[t]!=c)
			vis[t]=c,d[t]=d[x]+1,q.push(t);
	}
}
int main()
{
	scanf("%d%d",&n,&k);
    assert(k);
	for(int i=1,a,b;i<n;++i)
		scanf("%d%d",&a,&b),adde(a,b);
	int a;
	for(int i=1;i<=k;++i)
		scanf("%d",&a),b[a]=1;
	bfs(a,1); bfs(ls,2);
	printf("%d\n",(d[ls]+1)/2);
}

