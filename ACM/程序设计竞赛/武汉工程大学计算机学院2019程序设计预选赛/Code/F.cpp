# include <iostream>	// kcxz
# include <cstdio>
 
const int mod = 998244353;
const int maxn = 1e6+5;
int a[maxn];

void init() {
    a[0] = 0;
    a[1] = 1;
    a[2] = 1;
    for (int i=3; i<maxn; i++) {
        a[i] = (a[i-1] + a[i-2]) % mod;
    }
}
 
int main() {
    init();
    int T;
    scanf("%d", &T);
     
    while (T--) {
        int t;
        scanf("%d", &t);
 
        printf("%d\n", a[t]);
    }
     
    return 0;
}
