#include<bits/stdc++.h>
using namespace std;

typedef long long s64;
typedef pair<int,int> pii;
template <typename T> void chmin(T &x,const T &y)
{
	if(x>y)x=y;
}
template <typename T> void chmax(T &x,const T &y)
{
	if(x<y)x=y;
}
#define rep(i,l,r) for(int i=l;i<=r;++i)
#define per(i,r,l) for(int i=r;i>=l;--i)
#define gc (c=getchar())
int read()
{
	char c;
	while(gc<'-');
	if(c=='-')
	{	
		int x=gc-'0';
		while(gc>='0')x=x*10+c-'0';
		return -x;
	}
	int x=c-'0';
	while(gc>='0')x=x*10+c-'0';
	return x;
}
const int N=3e6+5;
int a[N],b[N],c[N][2],st[N];
struct Info
{
	s64 pre,suf,sum;
	Info ()=default;
	Info (int x)
	{
		pre=suf=max(x,0);sum=x;
	}
	Info (s64 _pre,s64 _suf,s64 _sum):pre(_pre),suf(_suf),sum(_sum)
	{
	}
	friend Info operator +(const Info &l,const Info &r)
	{
		return Info(max(l.pre,l.sum+r.pre),max(r.suf,r.sum+l.suf),l.sum+r.sum);
	}
};
Info mx[N],mn[N];
s64 ans=-3e18;

void work(int x)
{
	int l=c[x][0],r=c[x][1];
	if(l)work(l);
	if(r)work(r);
	chmax(ans,a[x]*(mx[l].suf+b[x]+mx[r].pre));
	chmax(ans,a[x]*-(mn[l].suf-b[x]+mn[r].pre));
	mx[x]=mx[l]+Info(b[x])+mx[r];
	mn[x]=mn[l]+Info(-b[x])+mn[r]; 
}

int main()
{
	//freopen("1.in","r",stdin);//freopen("tmp","w",stdout);
	int n=read();
	rep(i,1,n)a[i]=read();
	rep(i,1,n)b[i]=read();
	int top=1;
	st[1]=1;
	rep(i,2,n)
	{
		while(top&&a[i]<a[st[top]])
		{
			c[st[top]][1]=c[i][0];
			c[i][0]=st[top];
			--top;
		}
		st[++top]=i;
	}
	while(top>1)
	{
		c[st[top-1]][1]=st[top];
		--top;
	}
	work(st[1]);
	cout<<ans;
}
