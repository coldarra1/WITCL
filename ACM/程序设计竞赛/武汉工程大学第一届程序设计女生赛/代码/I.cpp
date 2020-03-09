# include <iostream>
# include <cstdio>
# include <algorithm>

using namespace std;

const int N = 1e6 + 5;
int n, m;
int val[N], w[N];

int main() {
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
		scanf("%d", val + i);
	for (int i = 1; i <= m; i++)
		scanf("%d", w + i);
	sort(val + 1, val + n + 1);
	sort(w + 1, w + m + 1);
	int res = -1;
	for (int i = 1; i <= n; i++)
		if (val[i] >= w[1]) {
			int j = 1;
			while (j <= m && val[i] >= w[j])
				j++;
			res = j - 1;
			break;
		}
	printf("%d\n", res);
	return 0;
}
