#include<cstdio>
#include<cstring>
#include<tuple>
#include <utility>
typedef unsigned long long ULL;
const int SIZE = 3000010;
ULL MOD;
char s[SIZE];
void mul(ULL* c1, ULL* c2, ULL *res){
    res[0] = (c1[0] * c2[0] + c1[1] * c2[2]) % MOD;
    res[1] = (c1[0] * c2[1] + c1[1] * c2[3]) % MOD;
    res[2] = (c1[2] * c2[0] + c1[3] * c2[2]) % MOD;
    res[3] = (c1[3] * c2[3] + c1[2] * c2[1]) % MOD;
}
int main() {
    int a,b;
    int x1,x2;
    scanf("%d%d%d%d", &x1, &x2, &a, &b);
    scanf("%s%llu",s, &MOD);
    int len = 0;
    for(; s[len]; len++);
    s[len-1]--;
    for(int i = len - 1; i >= 0 && s[i] < '0'; i--){
        s[i] = '9';
        s[i-1]--;
    }
    ULL now0 = x1, now1 = x2;
    ULL d[4][4];
    d[0][0] = 0;
    d[0][1] = 1;
    d[0][2] = b;
    d[0][3] = a;
    for(int it = len - 1; it >= 0; it--){
        memset(d[1], 0, sizeof(ULL) * 12);
        for(int p = 1; p < 4; p++){
            mul(d[p-1], d[p-1], d[p]);
        }
        s[it] -= '0';
        for(int p = 0; p < 4; p++){
            if((s[it] >> p) & 1){
                ULL* ml = d[p];
                std::tie(now0, now1) = std::make_pair((ml[0] * now0 + ml[1] * now1) % MOD,(ml[2] * now0 + ml[3] * now1) % MOD);
            }
        }
        mul(d[1], d[3], d[0]);
    }
    printf("%llu\n", now1);
    return 0;
}
