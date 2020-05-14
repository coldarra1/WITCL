# include <iostream>
# include <algorithm>
# include <cstring>

const int MAXN = 1e3 + 5;
const int NINF = 0xc0c0c0c0;
int v[MAXN];
int dp[MAXN];
int n;
int s;
int t;

int fmax(int num) {
	int max = NINF;
	for (int i=num-t; i<=num-s; i++) {
		if (i>=1 && dp[i] > max) {
			max = dp[i];
		}
	}
	
	return max;
}

int main() {
	int T;
	std::cin >> T;
	while (T--) {
		memset(dp, 0xc0, sizeof(dp));
		std::cin >> n >> s >> t;
		for (int i=1; i<=n; i++) {
			std::cin >> v[i];
		}
		
		dp[1] = v[1];
		for (int i=2; i<=n; i++) {
			if (fmax(i) == NINF) {
				dp[i] = NINF;
			} else {
				dp[i] = fmax(i) + v[i];
			}
		}
		
		if (dp[n] != NINF) {
			std::cout << dp[n] << "\n";
		} else {
			std::cout << "-1\n";
		}
	}
	
	return 0;
}
