#include <bits/stdc++.h>
#define MAXN 200005
using namespace std;

const long long M=1000000007;

int T,n,a[MAXN];
long long inv[MAXN],sinv[MAXN],ans,C;

inline long long fpow(long long a,long long b)
{
	a%=M;long long r=1;
	for (;b;b>>=1,(a*=a)%=M) if (b&1) (r*=a)%=M;
	return r;
}

void init(int n)
{
	inv[1]=1;
	for (int i=2;i<=n;i++) inv[i]=(M-M/i)*inv[M%i]%M;
	for (int i=1;i<=n;i++) sinv[i]=(sinv[i-1]+inv[i])%M;
	return ;
}

inline void Solve()
{
	scanf("%d",&n);C=ans=0;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]);
	for (int i=1,p=n>>1;i<=p;i++)
	{
		long long cov=i;
		cov+=i*(sinv[n-i]-sinv[i]+M)%M;cov%=M;
		(C+=i*inv[n-i+1]%M)%=M;(cov+=C)%=M;
		(ans+=a[i]*cov%M)%=M;(ans+=a[n+1-i]*cov%M)%=M;
	}
	if (n&1)
	{
		long long cov=0;
		for (int i=1;i<=n;i++) (cov+=min(i,n+1-i)*inv[i]%M)%=M;
		(ans+=cov*a[(n>>1)+1]%M)%=M;
	}
	printf("%lld\n",ans*fpow(1LL*n*(n+1)/2,M-2)%M);
	return ;
}

int main()
{
	init(200000);
	scanf("%d",&T);
	while (T--) Solve();
	return 0;
}
