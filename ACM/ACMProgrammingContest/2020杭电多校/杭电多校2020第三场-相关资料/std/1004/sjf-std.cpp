#include <bits/stdc++.h>
using namespace std;
int main()
{
	int t,n,p,i,x,now,ans;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&p);
		map<int,int> mp;
		mp[0]=1;
		now=0;
		ans=0;
		for(i=1;i<=n;i++)
		{
			scanf("%d",&x);
			now=(now+x)%p;
			if(mp.count(now))
			{
				ans++;
				now=0;
				mp.clear();
				mp[0]=1;
			}
			else mp[now]=1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
