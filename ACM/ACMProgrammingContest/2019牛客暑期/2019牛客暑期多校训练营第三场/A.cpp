#include<bits/stdc++.h>
#define N 100005
#define M 200005
#define U 1005
using namespace std;
typedef long long LL;
int Go[M<<1],Next[M<<1],Value[M<<1],End[N],cnt;
int be[M],tag[M],u[M],v[M],id[M],val[M];
LL F[U][U],G[U][U],key[N];
int st[U],ed[U],d[N],Q[N],n,m,S,tot;
void add(int u,int v,int w){
	Go[++cnt]=v;Value[cnt]=w;
	Next[cnt]=End[u];End[u]=cnt;
}
void Force(int l,int r){
	int k=be[l];
	for (int i=l;i<=r;i++){
		val[i]^=1;
		if (d[u[i]]>S){
			F[k][id[u[i]]]^=key[v[i]];
			G[k][id[u[i]]]^=key[v[i]];
		}
		if (d[v[i]]>S){
			F[k][id[v[i]]]^=key[u[i]];
			G[k][id[v[i]]]^=key[u[i]];
		}
	}
}
void Update(int l,int r){
	int u=be[l],v=be[r];
	if (u==v) return Force(l,r);
	for (int i=u+1;i<v;i++) tag[i]^=1;
	Force(l,ed[u]);Force(st[v],r);
}
LL Query(int x){
	LL ret=0;
	if (d[x]<=S){
		for (int i=End[x];i;i=Next[i])
			if (val[Value[i]]^tag[be[Value[i]]])
				ret^=key[Go[i]];
	}
	else {
		for (int i=1;i<=tot;i++)
			ret^=tag[i]?G[i][id[x]]:F[i][id[x]];
	}
	//printf("%d %lld\n",x,ret);
	return ret;
}
int Judge_Linux(){
	for (int i=1;i<=10;i++)
		if (rand()>32767) return 1;
	return 0;
}
void read(int &x){
	char ch = getchar();x = 0;
	for (; ch < '0' || ch > '9'; ch = getchar());
	for (; ch >='0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
}
LL Rand1(){return ((LL)rand()<<30LL)+rand();}
LL Rand2(){return ((LL)rand()<<45LL)+((LL)rand()<<30LL)+((LL)rand()<<15LL)+rand();}
int main(){
	int Linux=Judge_Linux();
	int sumn=0,summ=0,sumq=0,T;
	scanf("%d",&T);
	while (T--){
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) End[i]=d[i]=0;cnt=0;
		for (int i=1;i<=n;i++) key[i]=Linux?Rand1():Rand2();
		for (int i=1;i<=m;i++){
			read(u[i]);read(v[i]);
			d[u[i]]++,d[v[i]]++;
			add(u[i],v[i],i);add(v[i],u[i],i);
		}
		for (S=1;S*S<=m;S++);--S;tot=0;
		for (int i=1;i<=m;i+=S){
			tag[++tot]=0;st[tot]=i;ed[tot]=min(i+S-1,m);
			for (int j=st[tot];j<=ed[tot];j++) be[j]=tot;
		}
		for (int i=1;i<=m;i++) val[i]=1;
		*Q=0;for (int i=1;i<=n;i++)
			if (d[i]>S) Q[++*Q]=i,id[i]=*Q;
		for (int i=1;i<=*Q;i++){
			for (int j=1;j<=tot;j++) F[j][i]=G[j][i]=0;
			for (int t=End[Q[i]];t;t=Next[t])
				F[be[Value[t]]][i]^=key[Go[t]];
		}
		int T;read(T);
		sumn+=n;summ+=m;sumq+=T;
		while (T--){
			int opt,l,r;read(opt);read(l);read(r);
			if (opt==1) Update(l,r);
				   else putchar((Query(l)==Query(r))+'0');
			//if ((T%100==0)) fprintf(stderr,"%d\n",T);
		}
		puts("");
	}
	fprintf(stderr,"%d %d %d\n",sumn,summ,sumq);
}
