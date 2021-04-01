#include<bits/stdc++.h>
#define N 100005
using namespace std;
map<int,int>G;
int a[N],n;char s[N];
int main(){
	//freopen("test7.in","r",stdin);
	scanf("%d",&n);
	scanf("%s",s+1);
	for (int i=1;i<=n;i++)
		a[i]=a[i-1]+((s[i]=='1')?1:-1);
		
	//a[r]-a[l-1]==0
	int ans=0;
	G[0]=0;
	for (int i=1;i<=n;i++)
		if (G.find(a[i])!=G.end())
			ans=max(ans,i-G[a[i]]);
		else
			G[a[i]]=i;
	
	int zero=0,one=0;
	for (int i=1;i<=n;i++)
		if (s[i]=='0') zero++;else one++;
	printf("%d %d\n",ans,min(zero,one)*2);
}
