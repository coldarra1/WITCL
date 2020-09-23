# include <iostream>

const int mod = 1000000007;

int fphi(int n) { 
	int result = n;

	for (int p = 2; p * p <= n; p++) { 		 
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

int qpow(int x, int p) {
	int ans = 1;
	while (p) {
		if (p & 1) {
			ans = 1ll * ans * x % mod;
		}
		
		x = 1ll * x * x % mod;
		p >>= 1;
	}
	
	return ans;
}

int c(int n, int m) {
	if (n < m) {
		return 0;
	}
	
	int ntr = 1;
	int dom = 1;
	
	for (int i=n-m+1; i<=n; i++) {
		ntr = 1ll * ntr * i % mod;
	}
	
 	for (int i=1; i<=m; i++) {
 		dom = 1ll * dom * i % mod;	
	}
	
	return 1ll * ntr * qpow(dom, mod-2) % mod;
}

int lucas(int n, int m) {
	if (0 == m) {
		return 1;
	} else {
		return 1ll * lucas(n / mod, m / mod) * c(n % mod, m % mod) % mod;
	}
}

int main() {
	int T;
	std::cin >> T;
	int rev = qpow(2, fphi(mod - 1));
	
	while (T--) {
		int n;
		std::cin >> n;
		
		int t1 = lucas(n, n/2);

		int t2 = qpow(rev, n);
		
		std::cout << 1ll * t1 * t2 % mod << "\n";
	}
	
	return 0;
}