# include <iostream>

typedef long long ll;

const ll mod = 1000000007;

ll fphi(ll n) { 
	ll result = n;

	for (ll p = 2; p * p <= n; ++p) { 		 
		if (n % p == 0) { 
			while (n % p == 0) 
				n /= p; 
				
			result -= result / p; 
		} 
	} 

	if (n > 1) 
		result -= result / n; 
		
	return result; 
} 

ll qpow(ll x, ll p) {
	ll ans = 1;
	while (p) {
		if (p & 1) {
			ans = ans * x % mod;
		}
		
		x = x * x % mod;
		p >>= 1;
	}
	
	return ans;
}

ll c(ll n, ll m) {
	if (n < m) {
		return 0;
	}
	
	ll ntr = 1;
	ll dom = 1;
	
	for (int i=n-m+1; i<=n; i++) {
		ntr = ntr * i % mod;
	}
	
 	for (int i=1; i<=m; i++) {
 		dom = dom * i % mod;	
	}
	
	return ntr * qpow(dom, mod-2) % mod;
}

ll lucas(ll n, ll m) {
	if (0 == m) {
		return 1;
	} else {
		return lucas(n / mod, m / mod) * c(n % mod, m % mod) % mod;
	}
}

int main() {
	int T;
	std::cin >> T;
	ll rev = qpow(2, fphi(mod - 1));
	
	while (T--) {
		ll n;
		std::cin >> n;
		
		ll t1 = lucas(n, n/2);

		ll t2 = qpow(rev, n);
		
		std::cout << t1 * t2 % mod << "\n";
	}
	
	return 0;
}

