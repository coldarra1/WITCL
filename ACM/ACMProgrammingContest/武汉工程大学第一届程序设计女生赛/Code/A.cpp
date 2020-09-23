# include <iostream>

typedef long long ll;
 
int main() {
    int T;
    std::cin >> T;
     
    while (T--) {
        ll n;
        ll k;
        std::cin >> n >> k;
        
        ll cnt = 0;
         
        while (k < n) {
            k = k * k;
            ++cnt;
        }
        std::cout << cnt << "\n";
    }
    
    return 0;
}
