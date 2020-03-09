# include <iostream>
 
int gcd(int a, int b) {
    int t = a;
    while (t) {
        t = a %b;
        a = b;
        b = t;
    }
     
    return a;
}
 
int lcc(int a, int b) {
     
    return 1;
}
 
int main() {
    int a;
    int b;
    int c;
     
    std::cin >> a >> b >> c;
     
    int t = a * b / gcd(a, b);
    t = t * c / gcd(t, c);
     
     
    std::cout << t * 3;
     
    return 0;
}
