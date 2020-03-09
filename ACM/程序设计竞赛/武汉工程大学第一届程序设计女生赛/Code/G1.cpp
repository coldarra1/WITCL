# include <iostream>

typedef long long ll;

ll mul(ll a, ll b, ll mod) {
	ll ans = 0;
	
	while (b) {
		if (b & 1) {
			ans = (ans + a) % mod;
		}
		
		a = 2 * a % mod;
		b >>= 1;
	}
	
	return ans;
}

ll qpow(ll x, ll p, ll mod) {
	ll ans = 1 % mod;
	
	while (p) {
		if (p & 1) {
			ans = mul(ans, x, mod);
		}
		
		x = mul(x, x, mod);
		p >>= 1;
	}
	
	return ans;
}

int main() {
	int T;
	std::cin >> T;
	
	while (T--) {
		ll n;
		ll m;
		ll p;
		std::cin >> n >> m >> p;
		
		ll mod = n * p;
		
		ll t1 = qpow(m, n, mod);
		ll t2 = m * qpow(m - 1, n - 1, mod) % mod;
		
		std::cout << (mod + t1 - t2) % mod << "\n";	
	}
	
	return 0;
}
