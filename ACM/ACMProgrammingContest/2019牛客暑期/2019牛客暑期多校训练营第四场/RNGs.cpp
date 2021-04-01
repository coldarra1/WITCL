#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned us;
int a[2005],n,T;
char tmp[2005];
namespace Classify1
{
us k=214013u,b=2531011u,d=((1u<<29)-1);
unordered_set<ll> vl;
void init()
{
	us K=1,B=0;
	for(int j=1;j<=1600;++j)
		K=K*k,B=B*k+b;
	us x=0;
	for(int s=0;s<=d+100000;s+=1600)
	{
		us t=x; ll ss=0;
		for(int j=0;j<61;++j)
		{
			if((t>>28)&1) ss^=1LL<<j;
			t=(t*k+b)&d;
		}
		vl.insert(ss);
		x=(x*K+B)&d;
	}
}
bool chk()
{
	ll t=0;
	for(int j=0;j+61<=n;++j)
	{
		if(j==0)
		{
			t=0;
			for(int w=0;w<61;++w)
				if(a[j+w]) t^=1LL<<w;
		}
		else
		{
			t>>=1; if(a[j+60]) t^=1LL<<60;
		}
		if(vl.count(t)) return 1;
	}
	return 0;
}
}
namespace Classify3
{
bool chk()
{
	vector<int> v={0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,0,1,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,0,1,0,1,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,0,1};
	for(int j=v.size();j<n;++j)
	{
		int w=a[j];
		for(int p=0;p<v.size();++p)
			if(v[p]) w^=a[j-1-p];
		if(w) return 0;
	}
	return 1;
}
}
int main()
{
	Classify1::init();
	scanf("%d",&T);
    for(int j=0;j<T;++j)
	{
		scanf("%s",tmp); n=strlen(tmp);
		for(int j=0;j<n;++j) a[j]=tmp[j]-48;
        int ans=-1;
		if(Classify1::chk()) ans=0;
		else if(Classify3::chk()) ans=2;
		else ans=1;
        printf("%d\n",ans);
	}
}

