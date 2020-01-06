# include <iostream>
# include <algorithm>
using namespace std;
 
const int maxn = 10010;
int dp[maxn];
 
void pre_work()
{
	for (int i = 1; i < maxn; i++) {
		dp[i] = i;
		for (int j = 1; j < i - j; j++)
			dp[i] = min(dp[i], dp[j] + dp[i - j]);
		for (int j = 1; j * j <= i; j++)
			if (i % j == 0)
				dp[i] = min(dp[i], dp[i / j] + dp[j]);
	}
	return;
}
 
int main()
{
	ios::sync_with_stdio(false);
	pre_work();
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		cout << dp[n] << endl;
	}
	return 0;
}
