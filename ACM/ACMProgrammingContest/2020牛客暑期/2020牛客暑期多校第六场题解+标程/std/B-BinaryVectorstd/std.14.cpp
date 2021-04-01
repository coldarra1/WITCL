#include <bits/stdc++.h>
#define pcc pair<char, char>
#define vi vector<int>
#define vl vector<ll>
#define rep(i, x, y) for(int i = x; i <= y; i ++)
#define rrep(i, x, y) for(int i = x; i >= y; i --)
#define rep0(i, n) for(int i = 0; i < (n); i ++)
#define per0(i, n) for(int i = (n) - 1; i >= 0; i --)
#define eps 1e-9
#define inf 0x3f3f3f3f
#define sz(x) (x).size()
#define ALL(x) (x).begin(), (x).cntd()
#define ll long long
//#pragma GCC optimize(2)
using namespace std;
const int N = 20000005;
const int mod = 1e9 + 7;
int qp(int x, int p)
{
	int ret = 1;
	while (p)
	{
		if (p & 1) ret = 1ll * ret * x % mod;
		p >>= 1;
		x = 1ll * x * x % mod;
	}
	return ret;
}
int inv(int x) 
{
	return qp(x, mod - 2);
}
int res[N], pw2[N], pww[N], pi2[N];
int ans[N];
void _init() 
{
	pw2[0] = 1, pi2[0] = 1;
	rep(i, 1, N - 1) pw2[i] = pw2[i - 1] * 2 % mod;
	int iv2 = (mod + 1) / 2;
	rep(i, 1, N - 1) pi2[i] = 1ll * pi2[i - 1] * iv2 % mod;
	pww[0] = 1;
	rep(i, 1, N - 1) pww[i] = 1ll * pww[i - 1] * pi2[i] % mod * pi2[i - 1] % mod;
	res[1] = 1;
	rep(i, 2, N - 1) res[i] = 1ll * res[i - 1] * pw2[i - 1] % mod * (pw2[i] - 1) % mod;
	rep(i, 1, N - 1)
	{
		res[i] = 1ll * res[i] * pww[i] % mod;
		ans[i] = ans[i - 1] ^ res[i];
	}
}
int main() 
{
	_init();
	int t;
	scanf("%d", &t);
	while (t--) 
	{
		int n;
		scanf("%d", &n);
		printf("%d\n", ans[n]);
	}
}

