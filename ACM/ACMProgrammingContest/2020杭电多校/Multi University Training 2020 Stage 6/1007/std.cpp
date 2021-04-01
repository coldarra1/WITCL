#include <bits/stdc++.h>
using namespace std;

typedef long long lint;

const int N = 2e5 + 10;
const int mod = 1e9 + 7;

int fpow (int a, int b) { int ret = 1; while (b) { if (b & 1) ret = 1ll * ret * a % mod; a = 1ll * a * a % mod; b >>= 1; } return ret; }
int add (int a, int b) { return (a += b) >= mod ? a - mod : a; }
int sub (int a, int b) { return (a -= b) >= 0 ? a : a + mod; }
int mul (long long a, int b) { return a * b % mod; }
int inv (int a) { return fpow(a, mod - 2); }

int t, a, b;

int p[N], pc;
bool ptag[N];
int f[N], low[N];

int s[N];

void sieve (int n = N - 1) {
	f[1] = low[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!ptag[i]) {
			p[++ pc] = i;
			f[i] = sub(i, 1);
			low[i] = i;
		}
		for (int j = 1, k; j <= pc && i * p[j] <= n; j++) {
			ptag[k = i * p[j]] = 1;
			if (i % p[j]) {
				low[k] = p[j];
				f[k] = mul(f[i], f[p[j]]);
			} else {
				low[k] = low[i] * p[j];
				if (low[i] == i) {
					if (low[i] == p[j])
						f[k] = sub(mod, p[j]);
					else 
						f[k] = 0;
				} else
					f[k] = mul(f[i / low[i]], f[low[i] * p[j]]);
				break;
			}
		}
	}
	for (int i = 1; i <= n; i ++) {
		s[i] = fpow(i, a);
		f[i] = mul(f[i], fpow(s[i], b));
	}
	for (int i = 1; i <= n; i ++) {
		f[i] = add(f[i], f[i - 1]);
		s[i] = add(s[i], s[i - 1]);
	}
	for (int i = 1; i <= n; i ++)
		s[i] = fpow(s[i], b);
}

int main (void) {

	scanf("%d%d%d", &t, &a, &b);
	sieve();

	while (t --) {
		int n;
		scanf("%d", &n);
		int ans = 0;
		for (int l = 1, r; l <= n; l = r + 1) {
			r = n / (n / l);
			ans = add(ans, mul(sub(f[r], f[l - 1]), s[n / l]));
		}
		printf("%d\n", ans);
	}
}
