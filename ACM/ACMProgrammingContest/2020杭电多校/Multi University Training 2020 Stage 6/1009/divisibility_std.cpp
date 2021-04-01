#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        long long b, x;
        scanf("%lld %lld", &b, &x);
        if (b % x == 1) {
            printf("T\n");
        }
        else {
            printf("F\n");
        }
    }
    return 0;
}
