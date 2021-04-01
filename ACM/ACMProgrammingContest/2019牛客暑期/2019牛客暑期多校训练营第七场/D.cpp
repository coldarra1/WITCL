#include <bits/stdc++.h>
using namespace std;
 
int getDigits(int p) {
    int ans = 0;
    while (p) {
        p /= 10;
        ans++;
    }
    return ans;
}
void gao(int n, int p) {
    int d = getDigits(p);
    if (n == getDigits(2*p)) {
        printf("%d\n", 2*p);
        return;
    }
    if (d > n) printf("T_T\n");
    else {
        printf("%d", p);
        n -= d;
        while (n) {
            n--;
            printf("0");
        }
        printf("\n");
    }
}
 
void solve() {
    int n, p;
    scanf("%d%d", &n, &p);
    gao(n, p);
}
 
char inName[10];
char outName[10];
int main() {
    solve();
    return 0;
}
