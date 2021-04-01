#include <bits/stdc++.h>

const int N = 5e3 + 5;

int n, k, ans[N];

int main() {
    scanf("%d%d", &n, &k);
    if ((n % 2 == 0 && k != n / 2) || (n % 2 == 1 && k != 0)) {
		printf("-1\n"); return 0;
    }
    ans[n] = n;
    if (n % 2 == 0) {
        ans[n - 1] = k;
        int x = k - 1, y = k + 1;
        for (int i = 1; i + 1 < n - 1; i += 2) {
            ans[i] = x--;
            ans[i + 1] = y++;
		}
   	} else { 
        int x = n / 2, y = n / 2 + 1;
        for (int i = 1; i + 1 < n; i += 2) {
            ans[i] = x--;
            ans[i + 1] = y++;
		}
    }
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
	}
	return 0;
}