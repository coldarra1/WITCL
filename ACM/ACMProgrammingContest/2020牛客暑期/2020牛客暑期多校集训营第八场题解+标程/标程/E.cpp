#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000;
long long sum[MAXN+10];

const int up = 50;
long long dp[MAXN + 10][up][3];

int main() {

	memset(sum, 0, sizeof(sum));
	for (int l = up; l <= MAXN; l++) {
		int mid = l+1;
		int r = l+2;
		for (int nl = 1; nl * l <= MAXN; nl++) {
			for (int m = 3; m*mid + l*nl <= MAXN; m++) {
				sum[m*mid+l*nl] += (m-1)/2;
			}
		}
		for (int nr = 0; nr*r <= MAXN; nr++) {
			for (int m = 3; m*mid + r*nr <= MAXN; m++) {
				sum[m*mid+r*nr] += (m-1)/2;
			}
		}
	}

	for (int i = 1; i < up; i++)
		dp[0][i][0] = 1;
	for (int i = 0; i <= MAXN; i++) {
		for (int j = 1; j < up; j++) {
			if (i + j <= MAXN) dp[i+j][j][0] += dp[i][j][0];
			if (i + j + 1 <= MAXN) {
				dp[i+j+1][j][1] += dp[i][j][0];
				dp[i+j+1][j][1] += dp[i][j][1];
			}
			if (i + j + 2 <= MAXN) {
				dp[i+j+2][j][2] += dp[i][j][0];
				dp[i+j+2][j][2] += dp[i][j][1];
				dp[i+j+2][j][2] += dp[i][j][2];
			}
		}
	}
	for (int i = 1; i <= MAXN; i++) {
		for (int j = 1; j < up; j++) {
			int x = i - j - j - 1 - j - 2;
			if (x >= 0) sum[i] += dp[x][j][0] + dp[x][j][1] + dp[x][j][2];
		}
	}

	for (int i = 1; i <= MAXN; i++)
		sum[i] += sum[i-1];


	int T;
	scanf("%d", &T);
	int iCase = 0;
	while (T--) {
		iCase++;
		int l, r;
		scanf("%d%d", &l, &r);
		printf("Case #%d: ", iCase);
		cout<<sum[r] - sum[l-1]<<endl;
	}
	return 0;
}
