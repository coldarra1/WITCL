# include <iostream>
 
void solve(int a, int b, int c) {
     
    if ( a == b && a == c && b == c) {
        printf("equilateral\n");
        return;
    }
     
    if (a +b<=c || a + c <= b || b + c<=a) {
        printf("error\n");
        return;
    }
     
    if (a*a + b * b== c*c || a*a + c*c==b*b || c*c+b*b==a*a) {
        printf("right\n");
        return;
    }
     
    printf("normal\n");
}
 
int main() {
    int T;
    std::cin >> T;
     
    while (T--) {
         
        int a;
        int b;
        int c;
        scanf("%d%d%d", &a, &b, &c);
         
        solve(a, b, c);
    }
         
    return 0;
}
