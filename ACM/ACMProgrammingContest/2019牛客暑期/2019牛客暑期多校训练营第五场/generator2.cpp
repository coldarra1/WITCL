#include<cstdio>
#include<algorithm>
const int AA = 1000000;
std::pair<int, int> d[AA];
int mypow(long long x, int y, int p){
    long long res = 1;
    while(y) {
        if(y & 1) res = res * x % p;
        x = x * x % p;
        y >>= 1;
    }
    return res;
}
int inv(int x, int p) {
    return mypow(x, p - 2, p);
}
int val[AA], pos[AA];
void solve() {
    long long n, x0, a, b, p;
    int Q;
    scanf("%lld%lld%lld%lld%lld%d", &n, &x0, &a, &b, &p, &Q);
    if(a==0){
        while(Q--){
            int v;
            scanf("%d", &v);
            if(v==x0)puts("0");
            else if(v==b)puts("1");
            else puts("-1");
        }
        return;
    }
    long long now = x0;
    int m = std::min((long long)AA, n);
    for(int i = 0; i < m; i++) {
        d[i] = {now, i};
        now = (now * a + b) %p;
    }
    sort(d, d + m);
    {
        int new_m = 0;
        for(int i = 0; i < m; i++) {
            val[new_m] = d[i].first;
            pos[new_m++] = d[i].second;
            while(i + 1 < AA && d[i + 1].first == d[i].first) i++;
        }
        m=new_m;
    }
    int BB = p / AA + 3;
    int inv_a = inv(a, p);
    int inv_b = (p - b) % p * inv_a % p;
    long long aa = 1, bb = 0;
    for(int i = 0; i < AA; i++) {
        aa = aa * inv_a % p;
        bb = (bb * inv_a + inv_b) % p;
    }
    while(Q--) {
        int v;
        scanf("%d", &v);
        int it=std::lower_bound(val, val + m, v) - val;
        if(it < m && val[it] == v) {
            printf("%d\n", pos[it]);
            continue;
        }
        if(n < AA) {
            puts("-1");
            continue;
        }
        bool suc = false;
        for(int i = 1; i <= BB; i++) {
            v = (aa * v + bb) % p;
            it = std::lower_bound(val, val + m, v) - val;
            if(it < m && val[it] == v) {
                suc = true;
                int res =  i * AA + pos[it];
                if(res >= n) res = -1;
                printf("%d\n", res);
                break;
            }
        }
        if(!suc) puts("-1");
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) solve();
    return 0;
}
