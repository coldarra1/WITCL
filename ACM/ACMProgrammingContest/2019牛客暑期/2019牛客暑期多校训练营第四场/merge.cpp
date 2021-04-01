#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
const int N=1e5+5;
int a[N];

namespace SPLAY
{
int fa[N],c[N][2],sz[N],mx[N];
void sc(int y,int x,bool d)
{
	c[y][d]=x;fa[x]=y; 
} 
void push_up(int x)
{
	mx[x]=max(max(mx[c[x][0]],mx[c[x][1]]),x);
	sz[x]=sz[c[x][0]]+sz[c[x][1]]+1;
}
bool get(int x)
{
	return x==c[fa[x]][1];
}
void rot(int x)
{
	int y=fa[x];bool d=get(x);
	if(!fa[y])fa[x]=0;
	else sc(fa[y],x,get(y));
	sc(y,c[x][!d],d);
	sc(x,y,!d);
	push_up(y);
}
void splay(int x)
{
	while(fa[x])
	{
		int y=fa[x];
		if(!fa[y]){rot(x);break;}
		rot(get(x)==get(y)?y:x);rot(x);
	}
	push_up(x);
}
int query(int x,int k)
{
	splay(x);
	while(k!=sz[c[x][0]]+1)
	if(k<=sz[c[x][0]])x=c[x][0];
	else
	{
		k-=sz[c[x][0]]+1;
		x=c[x][1];
	}
	return x;
}
int find_fir(int x)
{
	int y=c[x][1];
	while(1)
	if(mx[c[y][0]]>x)y=c[y][0]; else
	if(y>x)return y; else
		y=c[y][1];
}
};

namespace ZKW
{
int d,a[N*3];
void init(int n)
{
	for(d=1;d<=n;d<<=1);d-=1;
}
void add(int i,int w)
{
	i+=d;
	for(;i;i>>=1)a[i]+=w;
}
int query(int p)
{
	int i=1;
	while(i<=d)
	if(p<=a[i*2])i*=2;
	else 
	{
		p-=a[i*2];
		i=i*2+1;
	}
	return SPLAY::query(i-d,p);
}
};

void init(int n)
{
	ZKW::init(n);
	int mx=0;
	rep(i,1,n)
	if(a[i]<mx)SPLAY::sc(a[i-1],a[i],1);
	else mx=a[i];
	per(i,n,1)
	{
		SPLAY::push_up(a[i]);
		if(SPLAY::fa[a[i]]==0)ZKW::add(a[i],SPLAY::sz[a[i]]);
	}
}

int query(int p)
{
	return ZKW::query(p);
}
void split(int x)
{
	while(1)
	{
		while(SPLAY::c[x][0])x=SPLAY::c[x][0];
		SPLAY::splay(x);
		if(SPLAY::mx[x]==x){ZKW::add(x,SPLAY::sz[x]);break;}
		int y=SPLAY::find_fir(x);
		SPLAY::splay(y);
		ZKW::add(x,SPLAY::sz[SPLAY::c[y][0]]);
		SPLAY::c[y][0]=SPLAY::fa[SPLAY::c[y][0]]=0;
		x=y;
	}
}
void merge(int m,int r)
{
	int ar=query(r);
	SPLAY::splay(ar);
	int cr_ar=SPLAY::c[ar][1];
	SPLAY::c[ar][1]=0;
	SPLAY::push_up(ar);
	
	int am=query(m);
	SPLAY::splay(am);
	int cr_am=SPLAY::c[am][1];
	SPLAY::c[am][1]=0;
	SPLAY::push_up(am);
	ZKW::add(SPLAY::mx[am],-SPLAY::sz[cr_am]);
	SPLAY::fa[cr_am]=0;
	if(cr_am)split(cr_am);
	
	ar=query(r);
	SPLAY::splay(ar);
	SPLAY::sc(ar,cr_ar,1);
	SPLAY::push_up(ar);
} 

int main()
{
//	freopen("1.in","r",stdin);
	int n,m;
	cin>>n>>m;
	rep(i,1,n)scanf("%d",a+i);
	init(n);
	while(m--)
	{
		int ty;
		scanf("%d",&ty);
		if(ty==1)
		{
			int l,m,r;
			scanf("%d%d%d",&l,&m,&r);
			assert(l==1&&m>=l&&m<r&&r<=n);
			merge(m,r);
		}
		else
		{
			int i;
			scanf("%d",&i);
			printf("%d\n",query(i));
		}
	}
}
