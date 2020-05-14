# include <iostream>
 
int main() {
    int T;
    std::cin >> T;
    while (T--) {
        double p;
        std::cin >> p;
         
        printf("%.6lf\n", std::min(1.0 * p / (1-p), 1.0));
    }  
     
    return 0;
}
