#include<bits/stdc++.h>
using namespace std;

const int mod = 998244353;

int fac[2020202], _fac[2020202];

int C(int n, int m)
{
	return 1ll * fac[n] * _fac[m] % mod * _fac[n - m] % mod;
}

int qpow(int n, int k)
{
	int ret = 1;
	while(k)
	{
		if(k&1)
			ret = 1ll * ret * n % mod;
		n = 1ll * n * n % mod;
		k /= 2;
	}
	return ret;
}

int main()
{
	fac[0] = 1;
	for(int i = 1; i <= 2e6; i++)
		fac[i] = 1ll * fac[i-1] * i % mod;
		
	_fac[2000000] = qpow(fac[2000000], mod - 2);
	for(int i = 2e6; i >= 1; i--)
		_fac[i - 1] = 1ll * _fac[i] * i % mod;
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int N, M, K;
		scanf("%d%d%d", &N, &M, &K);
		
		int ans = 0;
		
		for(int i = 0; i <= min(N, M) - K; i++)
		{
			//cout << C(i + K - 1, K - 1) << " " << C(N - i - 1, K - 1) << " " <<  C(M - i - 1, K - 1) << endl;
			ans += 1ll * C(i + K - 1, K - 1) * C(N - i - 1, K - 1) % mod * C(M - i - 1, K - 1) % mod;
			if(ans >= mod)
				ans -= mod;
		}
		printf("%d\n", ans);
	}
	return 0;
}