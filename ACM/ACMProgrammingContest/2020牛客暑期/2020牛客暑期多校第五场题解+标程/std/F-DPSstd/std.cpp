#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
#define read(a) scanf("%d", &a)
#define x first
#define y second

#define N 105
int n;
int d[N];

int main() {
	read(n);
	int maxd = 0;
	for (int i = 1; i <= n; i++) {
		read(d[i]);
		maxd = max(d[i], maxd);
	}
	for (int i = 1; i <= n; i++) {
		int s = (d[i] * 50u + maxd - 1) / maxd;
		putchar('+');
		for (int j = s; j--; putchar('-'));
		putchar('+');
		putchar('\n');
		putchar('|');
		for (int j = s; j--; putchar(j == 0 && d[i] == maxd ? '*' : ' '));
		putchar('|');
		printf("%d", d[i]);
		putchar('\n');
		putchar('+');
		for (int j = s; j--; putchar('-'));
		putchar('+');
		putchar('\n');
	}
}
