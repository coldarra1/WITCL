#include <bits/stdc++.h>
using namespace std;
 
int a[100];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        assert(n >= 0 && n <= 20);
        for (int i = 0; i <= n; i++)
            scanf("%d", &a[i]);
        if (n <= 1 || (n == 2 && (long long)a[1]*a[1] < (long long)4*a[0]*a[2])) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}
