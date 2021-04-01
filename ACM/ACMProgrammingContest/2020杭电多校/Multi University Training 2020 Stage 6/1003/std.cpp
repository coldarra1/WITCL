#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
const int mod = 998244353;

int fpow (int a, int b) { int ret = 1; while (b) { if (b & 1) ret = 1ll * ret * a % mod; a = 1ll * a * a % mod; b >>= 1; } return ret; }
int add (int a, int b) { return (a += b) >= mod ? a - mod : a; }
int sub (int a, int b) { return (a -= b) >= 0 ? a : a + mod; }
int mul (long long a, int b) { return a * b % mod; }

int f[N], invf[N], inv[N], pw[N];
int dp[2][N];

void predeal (int n = N - 1) {
	f[0] = f[1] = 1;
	for (int i = 2; i <= n; i ++) f[i] = 1ll * f[i - 1] * i % mod;
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i ++) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	invf[0] = invf[1] = 1;
	for (int i = 2; i <= n; i ++) invf[i] = 1ll * invf[i - 1] * inv[i] % mod;
	pw[0] = 1;
	for (int i = 1; i <= n; i ++) pw[i] = 1ll * pw[i - 1] * inv[2] % mod;
	
	dp[0][1] = 2;
	for (int i = 2; i <= n; i ++) {
		dp[0][i] = 2 + dp[1][i - 1];
	 	dp[1][i] = 2 + dp[0][i - 2];
	}
}

int bi (int a, int b) { return (a >= b && b >= 0) ? 1ll * f[a] * invf[b] % mod * invf[a - b] % mod : 0; }

int solve (int x, int y, int i, int j) {
	if ((i + j) % 3) return 0;
	int dx = x - i, dy = y - j, t = (dx + dy) / 3;
	int p = mul(bi(t, dx - t), pw[t + 1]);
	if (j == 2) return mul(p, add(mul(2, t + 1), add(dp[0][i - 1], dp[1][i - 2])));
	else return mul(p, add(t + 1, dp[1][i - 1]));
}

int main (void) {
	predeal();

	int kase;
	scanf("%d", &kase);
	while (kase --) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		if ((x + y + z) % 3) {
			puts("-1");
			continue;
		}
		if (x > y) swap(x, y);
		if (x > z) swap(x, z);
		if (y > z) swap(y, z);
		x = z - x; y = z - y;

		if (y == 1 || y == 0) {
			printf("%d\n", dp[y][x]);
			continue;
		} 

		// dp[x][3] -> dp[x - 2][2], dp[x - 1][1]
		// dp[x][2] -> dp[x - 2][1], dp[x - 1][0]
		// dp[3][3] -> dp[1][2], dp[2][1]
		int ans = 0;
		if (y >= 3) {
		 	for (int i = 4; i <= x; i ++)
				ans = add(ans, solve(x, y, i, 3));
		}
		if (y >= 2) {
			for (int i = 4; i <= x; i ++) 
				ans = add(ans, solve(x, y, i, 2));
		}
		if (x >= 3) {
			for (int i = 4; i <= y; i ++)
				ans = add(ans, solve(y, x, i, 3));
		}
		if (x >= 2) {
			for (int i = 4; i <= y; i ++) 
				ans = add(ans, solve(y, x, i, 2));
		}
		if (x >= 3 && y >= 3) {
			int dx = x - 3, dy = y - 3, t = (dx + dy) / 3;
			int p = mul(bi(t, dx - t), pw[t]);
			ans = add(ans, mul(t + 3, p));
		}
		printf("%d\n", ans);
	}
}