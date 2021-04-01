#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pb push_back
int T; ll a,x,y;
void sol()
{
	scanf("%lld",&a);
	vector<ll> bb[2];
	for(int i=0;i<=60;++i)
		if((a>>i)&1) bb[i&1].pb(1LL<<i);
	if(a%3==0) printf("1 %lld\n",a);
	else if(bb[0].size()+bb[1].size()<=2) for(;;);
	else
	{
		int s=(a%3==2);
		if(bb[s].size())
		{
			x=a-bb[s][0];
			if(bb[!s].size()) y=bb[s][0]+bb[!s][0];
			else y=a-bb[s][1];
		}
		else x=a-bb[!s][0]-bb[!s][1],
		y=bb[!s][0]+bb[!s][1]+bb[!s][2];
		printf("2 %lld %lld\n",y,x);
	}
}
int main()
{
	scanf("%d",&T);
	while(T--) sol();
}

