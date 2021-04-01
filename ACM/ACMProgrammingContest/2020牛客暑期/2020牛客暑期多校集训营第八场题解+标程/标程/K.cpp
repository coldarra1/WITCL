#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
int a[MAXN];
int b[MAXN];
long long suma[MAXN];
pair<long long, int> pp[MAXN];
int sta[MAXN];

const long long TT = 10000000LL;

int main() {
	int T;
	scanf("%d", &T);
	int iCase = 0;
	while (T--) {
		int n;
		scanf("%d", &n);
		suma[0] = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			suma[i] = suma[i-1] + a[i];
			pp[i] = make_pair(suma[i], i);
		}
		for (int i = 1; i <= n; i++) {
			scanf("%d", &b[i]);
		}
		int top = 0;
		for (int i = 1; i <= n; i++) {
			if (top == 0) sta[top++] = i;
			else if (b[sta[top-1]] > b[i]) sta[top++] = i;
		}
		sort(pp+1, pp+n+1);
		int ans1 = 0;
		int now = 0;
		long long pos1 = 0, pos2 = 0;
		long long neg1 = 0, neg2 = 0;
		
		for (int i = n; i >= 1; i--) {
			long long c = pp[i].first;
			int id = pp[i].second;
			while (sta[top-1] > id) top--;

			int tmp = b[sta[top-1]] - ans1;
			if ((c >= 0 && tmp >= 0) || (c <= 0 && tmp <= 0)) {
				c = abs(c);
				tmp = abs(tmp);
				pos1 += (c/TT) * tmp;
				pos2 += (c%TT) * tmp;
				if (pos2 >= TT) {
					pos1 += pos2 / TT;
					pos2 %= TT;
				}
			} else {
				c = abs(c);
				tmp = abs(tmp);
				neg1 += (c/TT) * tmp;
				neg2 += (c%TT) * tmp;
				if (neg2 >= TT) {
					neg1 += neg2 / TT;
					neg2 %= TT;
				}
			}

			ans1 = b[sta[top-1]];
		}
		iCase++;
		printf("Case #%d: %d ", iCase, ans1);

		if (pos1 > neg1 || (pos1 == neg1 && pos2 >= neg2)) {
			pos2 -= neg2;
			if (pos2 < 0) {
				pos2 += TT;
				pos1--;
			}
			pos1 -= neg1;
			if (pos1 == 0) printf("%lld\n", pos2);
			else printf("%lld%07lld\n", pos1, pos2);
		} else {
			neg2 -= pos2;
			if (neg2 < 0) {
				neg2 += TT;
				neg1--;
			}
			neg1 -= pos1;
			printf("-");
			if (neg1 == 0) printf("%lld\n", neg2);
			else printf("%lld%07lld\n", neg1, neg2);
		}
	}
	return 0;
}
