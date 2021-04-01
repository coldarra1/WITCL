#include<bits/stdc++.h>
using namespace std;

typedef unsigned int u32;
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
const int N=5e4+5,L=10,B=N/L+5;
struct Base
{
	static const int L=32;
	u32 a[L];
	u32& operator [](int x)
	{
		return a[x];
	}
	u32 operator [](int x)const
	{
		return a[x];
	}
	void ins(u32 x)
	{
		per(i,L-1,0)
		if((x>>i)&1)
		if(a[i])x^=a[i];
		else {a[i]=x;break;}
	}
	bool check(u32 x)
	{
		per(i,L-1,0)
		if((x>>i)&1)
		if(a[i])x^=a[i];
		else return 0;
		return 1;
	}
	void init()
	{
		int sz;
		scanf("%d",&sz);
		while(sz--)
		{
			u32 x;
			scanf("%u",&x);
			ins(x);
		}
	}
friend Base intersection(const Base &a,const Base &b)
{
	Base ans={},c=b,d=b;
	rep(i,0,L-1)
	{
		u32 x=a[i];
		if(!x)continue;
		int j=i;u32 T=0;
		for(;j>=0;--j)
		if((x>>j)&1)
		if(c[j]){x^=c[j];T^=d[j];}
		else break;
		if(!x)ans[i]=T;
		else {c[j]=x;d[j]=T;}
	}
	return ans;
}
};
Base a[N],f[15][B];

bool brute_check(int l,int r,u32 x)
{
	rep(i,l,r)
	if(!a[i].check(x))return 0;
	return 1;
}
bool check(int l,int r,u32 x)
{
//	Base ans=a[l];
//	rep(i,l,r)ans=intersection(ans,a[i]);
//	return ans.check(x);
	int bl=(l-1)/L,br=(r-1)/L;
	if(bl+1>=br)return brute_check(l,r,x);
	if(!brute_check(l,(bl+1)*L,x)||!brute_check(br*L+1,r,x))return 0;
	l=bl+1;r=br-1;
	int j=31-__builtin_clz(r-l+1);
	return intersection(f[j][l],f[j][r-(1<<j)+1]).check(x);
}

int main()
{
//	freopen("data10.in","r",stdin);freopen("tmp","w",stdout);
	int n,m;
	cin>>n>>m;
	rep(i,1,n)a[i].init();	
	
	rep(i,0,(n-1)/L)
	{
		f[0][i]=a[i*L+1];
		rep(j,i*L+2,min(n,(i+1)*L))f[0][i]=intersection(f[0][i],a[j]);
	}
	rep(i,1,14)
	rep(j,0,(n-1)/L-(1<<i)+1)f[i][j]=intersection(f[i-1][j],f[i-1][j+(1<<i-1)]);
	
	while(m--)
	{
		int l,r;u32 x;
		scanf("%d%d%u",&l,&r,&x);
	//	assert(check(l,r,x)==brute_check(l,r,x));
		if(check(l,r,x))puts("YES");
		else puts("NO"); 
	}
}
