# include <iostream>
 
typedef long long ll;
 
const ll mod = 20190930;
 
ll fphi(ll n) {
    ll result = n;
     
    for (int p=2; p*p <=n; p++) {
        if (0 == n % p) {
            while (0 == n%p) {
                n /= p;
            }
             
            result -= result / p;
        }
    }
     
    if (n > 1) {
        result -= result / n;
    }
     
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
 
 
 
int main() {
    int T;
    std::cin >> T;
     
    while (T--) {
        ll a;
        ll b;
        ll c;
        ll d;
         
        std::cin >> a >> b >> c >> d;
         
        ll x = qpow(c, fphi(mod)-1);
        ll t2 = qpow(x, d);
        ll t1 = qpow(a, b);
         
        std::cout << (t1 * t2) % mod << std::endl;
    }
     
    return 0;
}
