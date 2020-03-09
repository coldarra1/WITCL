# include <iostream>

template <typename T> 
void read(T &val) { 
	T x = 0; 
	int bz = 1; 
	char c; 
	
	for (c = getchar(); (c<'0' || c>'9') && c != '-'; 
	c = getchar()); 
	
	if (c == '-') { 
		bz = -1; 
		c = getchar(); 
	}
	
	for (; c >= '0' && c <= '9'; c = getchar()) 
		x = x * 10 + c - 48; 
		
	val = x * bz; 
}

template <typename T>
void put(T x){  
    static char	s[20];  
    int bas;  
  
    if(x < 0) {  
        putchar('-');  
        x = -x;  
    }  
    
    if(x == (T)(0)) {  
        putchar('0');  
        return;  
    }  
    
    bas = 0;  
    for(;x;x/=10) 
		s[bas++] = x%10+'0';  
		
    for(;bas--;) 
		putchar(s[bas]);  
}  

__int128 qpow(__int128 x, __int128 p, __int128 mod) {
	__int128 ans = 1 % mod;
	
	while (p) {
		if (p & 1) {
			ans = ans * x % mod;
		}
		
		x = x * x % mod;
		p >>= 1;
	}
	
	return ans;
}

int main() {
	int T;
	std::cin >> T;
	
	while (T--) {
		__int128 n;
		__int128 m;
		__int128 p;
		read(n);
		read(m);
		read(p);
		
		__int128 mod = n * p;
		
		__int128 t1 = qpow(m, n, mod);
		__int128 t2 = m * qpow(m - 1, n - 1, mod) % mod;
		
		put((mod + t1 - t2) % mod);
		std::cout << "\n";
	}
	
	return 0;
}

