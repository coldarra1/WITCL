#include <bits/stdc++.h>
using namespace std;


typedef long long LL;

vector<pair<int, int> > plist;

int pow_mod(int x, int k, int p)
{
	int ret = 1;
	for (; k; k>>=1)
	{
		if (k&1) ret = 1LL*ret*x%p;
		x = 1LL*x*x%p;
	}
	return ret;
}

int f(int n, int k)
{
	int d = 1;
	for (auto pv: plist)
	{
	 	int t = (pv.second+k-1) / k;
	 	while (t--) d *= pv.first;
    }
	return n/d;
}

int main()
{
    int T, n, m, p, d, D;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d %d", &p, &n, &m);
		if (p == 2 || p == 5) {puts("0"); continue;}
		if (p == 3) // 10^d = 1 mod 27
		{
			//phi(27) = 18
			D = 18;
			p = 27;
		}
		else D = p-1;
		assert(pow_mod(10, D, p) == 1);
	  
		d = 1e9;
		for (int i = 1; i*i <= D; ++i)
		{
			if (D % i) continue;
			if (pow_mod(10, i, p) == 1)
			   d = min(d, i);
            if (pow_mod(10, D/i, p) == 1)
               d = min(d, D/i);
		}
		for (int i = 2; i*i <= d; ++i)
		{
		 	if (d % i) continue;
			int c = 0;
			while (d % i == 0) ++c, d /= i;
			plist.push_back(make_pair(i, c));	
		}
		if (d != 1) plist.push_back(make_pair(d, 1));
		LL ans = 0;
		for (int i = 1; i <= 30 && i <= m; ++i)
			ans += f(n, i);
		if (m > 30) ans += 1LL*(m-30)*f(n, 30);
		printf("%lld\n", ans);
		plist.clear();
	}
	return 0;
}