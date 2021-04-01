#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SZ 666666
const int MOD=998244353;
struct uu {ll t[3];};
uu operator * (uu a,uu b)
{
	uu c;
	for(int i=0;i<3;++i) c.t[i]=0;
	for(int i=0;i<3;++i)
		for(int j=0;j<3;++j)
			(c.t[(i+j)%3]+=a.t[i]*b.t[j])%=MOD;
	return c;
}
ll n,t,u=1;
int cw[2];
ll C[80][80];
uu gx[2][77];
ll qp(ll a,ll b)
{
	ll x=1; a%=MOD;
	while(b)
	{
		if(b&1) x=x*a%MOD;
		a=a*a%MOD; b>>=1;
	}
	return x;
}
int main()
{
	for(int i=0;i<80;++i)
	{
		C[i][0]=1;
		for(int j=1;j<=i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
	}
	int T; cin>>T;
	{
		uu w; w.t[0]=1;
		w.t[1]=w.t[2]=0;
		gx[0][0]=gx[1][0]=w;
	}
	for(int u=1;u<=2;++u)
	{
		uu w; w.t[3^u]=0;
		w.t[u]=w.t[0]=1;
		gx[u-1][1]=w;
	}
	for(int u=0;u<2;++u)
		for(int i=2;i<=70;++i)
			gx[u][i]=gx[u][i-1]*gx[u][1];
	while(T--)
	{
		memset(cw,0,sizeof cw);
		cin>>n>>t; u=1;
		while(u<=t)
		{
			if(t&u)
				++cw[u%3-1];
			u<<=1;
		}
		ll ans=0;
		for(int a=0;a<=cw[0];++a)
			for(int b=0;b<=cw[1];++b)
			{
				ll co=C[cw[0]][a]*C[cw[1]][b]%MOD;
				if((cw[0]^a^cw[1]^b)&1) co=-co;
				ans+=co*qp((gx[0][a]*gx[1][b]).t[0],n);
				ans%=MOD;
			}
		ans=(ans%MOD+MOD)%MOD;
		cout<<ans<<"\n";
	}
}

