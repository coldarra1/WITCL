#include<cstdio>
#include<algorithm>
const int MAX_V = 3 * 1000 * 1000;
int composition[MAX_V + 1];
// a*x+b*y=z
struct gcd_t {long long x,y,z;};
gcd_t gcd(long long a,long long b) {
    if(b==0)return (gcd_t){1,0,a};
    gcd_t t=gcd(b,a%b);
    return (gcd_t){t.y,t.x-t.y*(a/b),t.z};
}
void solve(int d, int a, int b) {
    int f = b / d;
    gcd_t ret = gcd(d,f);
    if(ret.x > 0) printf("%lld %d %lld %d\n",ret.x*a,f,-ret.y*a,d);
    else printf("%lld %d %lld %d\n",ret.y*a,d,-ret.x*a,f);
}
void solve() {
    int a, b;
    scanf("%d%d", &a, &b);
    int g=std::__gcd(a,b);
    if(g != 1) {
        printf("%d %d %d %d\n",a/g+1,b/g,1,b/g);
        return;
    }
    if(!composition[b]) puts("-1 -1 -1 -1");
    else solve(composition[b], a, b);
}
#include<bitset>
std::bitset<MAX_V+1>p;
void pre() {
    for(int i = 2; i * i <= MAX_V; i++) {
        if(p[i]) continue;
        for(int j = i + i; j <= MAX_V; j += i) {
            p[j] = 1;
            if(!composition[j]) {
                int now = i;
                while(j % (now * i) == 0) now *= i;
                if(now < j) {
                    composition[j] = now;
                }
            }
        }
    }
}
int main() {
    pre();
    int T;
    scanf("%d", &T);
    while(T--) {
        solve();
    }
    return 0;
}
