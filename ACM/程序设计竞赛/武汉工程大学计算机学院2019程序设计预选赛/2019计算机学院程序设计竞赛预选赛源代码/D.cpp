# include <iostream>	// kcxz
 
bool isPrime(int n) {
    if (n <= 1)
        return false;
         
    if (n <= 3)
        return true;
 
    if (n % 2 == 0 || n % 3 == 0)
        return false;
 
    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
 
    return true;
}
 
int main() {
    int n;
    std::cin >> n;
     
    int cnt = 0;
    for(int i=2; i<=n; i++) {
        if (n % i == 0) {
            if (isPrime(i)) {
                cnt += i;
            }
        }
    }
     
    if (cnt > 610) {
        std::cout << "a sdl wsl";
    } else {
        std::cout << "tcl";
    }
     
    return 0;
}

//# include <iostream>
//
//int main() {
//	int n;
//	std::cin >> n;
//	
//	int sum = 0;
//	for (int i=2; i<=n; i++) {
//		if (0 == n%i) {
//			sum += i;
//			
//			while (0 == n%i) {
//				n /= i;
//			}
//		}
//	}
//	
//	if (sum > 610) {
//		std::cout << "a sdl wsl";
//	} else {
//		std::cout << "tcl";
//	} 
//	
//	return 0;
//} 
