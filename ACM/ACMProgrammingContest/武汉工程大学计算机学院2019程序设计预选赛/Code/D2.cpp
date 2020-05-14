# include <iostream>

int main() {
	int n;
	std::cin >> n;
	
	int sum = 0;
	for (int i=2; i<=n; i++) {
		if (0 == n%i) {
			sum += i;
			
			while (0 == n%i) {
				n /= i;
			}
		}
	}
	
	if (sum > 610) {
		std::cout << "a sdl wsl";
	} else {
		std::cout << "tcl";
	} 
	
	return 0;
} 
