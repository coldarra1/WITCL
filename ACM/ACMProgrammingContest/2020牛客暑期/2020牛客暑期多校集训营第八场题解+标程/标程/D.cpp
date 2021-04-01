#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9+7;
int dp[100010];
// 整数拆分模板
void number_partition() {
	memset(dp, 0, sizeof(dp));
	dp[0] = 1;
	for (int i = 1; i <= 100000; i++) {
		for (int j = 1, r = 1; i - (3 * j * j - j) / 2 >= 0; j++, r *= -1) {
			dp[i] += dp[i - (3 * j * j - j) / 2] * r;
			dp[i] %= MOD;
			dp[i] = (dp[i] + MOD) % MOD;
			if (i - (3 * j * j + j) / 2 >= 0) {
				dp[i] += dp[i - (3 * j * j + j) / 2] * r;
				dp[i] %= MOD;
				dp[i] = (dp[i] + MOD)%MOD;
			}
		}
	}
}

int main() {
	number_partition();

	int T;
	int iCase = 0;
	scanf("%d", &T);
	while (T--) {
		iCase++;
		long long n;
		int p;
		cin>>n>>p;
		long long ans = dp[n%p];
		long long n1 = n/p;
		while (n1) {
			ans = ans * (n1%p + 1) % MOD;
			n1 /= p;
		}
		printf("Case #%d: %d\n", iCase, (int) ans);
	}
	return 0;
}
