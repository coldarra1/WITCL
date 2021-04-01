#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;
const int mo = 1e9 + 7;

int prime[N], prime_cnt[N];

void sieve(int n) {
	for(int i = 2; i <= n; i++) {
		if(!prime_cnt[i]) {
			prime[++*prime] = i;
			prime_cnt[i] = 1;
		}
		for(int j = 1; j <= *prime && i * prime[j] <= n; j++) {
			prime_cnt[i * prime[j]] = prime_cnt[i] + 1;
			if(i % prime[j] == 0) {
				break;
			}
		}
	}
}

int pow(int x, int m) {
	int nowans = 1;
	while(m) {
		if(m & 1) {
			nowans = 1ll * nowans * x % mo;
		}
		x = 1ll * x * x % mo;
		m >>= 1;
	}
	return nowans;
}

int main() {
	sieve(1000000);
	int T;
	scanf("%d", &T);
	while(T--) {
		int n, c;
		scanf("%d%d", &n, &c);
		printf("%d\n", pow(c, prime_cnt[n]));
	}
}