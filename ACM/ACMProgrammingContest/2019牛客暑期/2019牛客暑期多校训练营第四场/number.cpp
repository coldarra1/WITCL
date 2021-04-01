#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define SZ 666666
char s[SZ]; int n,w[SZ],cn[3];
int main()
{
	scanf("%s",s+1); n=strlen(s+1);
	for(int i=1;i<=n;++i)
		w[i]=(w[i-1]+s[i])%3;
	ll ans=0;
	for(int i=1;i<=n;++i)
	{
		if(s[i]=='0')
		{
			++ans;
			if(s[i-1]=='0')
				ans+=cn[w[i]];
		}
		cn[w[i-1]]++;
	}
	printf("%lld\n",ans);
}

