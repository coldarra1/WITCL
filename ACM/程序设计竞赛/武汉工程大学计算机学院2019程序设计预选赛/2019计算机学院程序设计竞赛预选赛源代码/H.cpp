# include <iostream>	// NQ
# include <cstdio>
# include <algorithm>

using namespace std;

const int N = 1e6 + 5;
int n, m, k, sum[N];
int q[N], hh, tt;

int main()
{
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &sum[i]);
		sum[i] += sum[i - 1];
	}
	int max_res = -0x3f3f3f3f;
	for (int i = 1; i <= n; i++) {
		if (hh <= tt && i - q[hh] > k)
			hh++;
		max_res = max(max_res, sum[i] - sum[q[hh]]);
		while (hh <= tt && sum[i] <= sum[q[tt]])
			tt--;
		q[++tt] = i;
	}
	while (m--) {
		int x;
		scanf("%d", &x);
		if (max_res >= x)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
