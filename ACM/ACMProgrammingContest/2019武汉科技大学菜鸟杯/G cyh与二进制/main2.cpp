#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll F(ll x)
{
    int c = 0;
    ll xt = x;
    for (int i = 0; i < 32; ++i)
    {
        if (x >> i & 1) {
            xt -= 1ll << i;
            c++;
        }
        if ((x >> i & 1) && (x >> (i + 1) & 1) == 0) {
            return xt + (1ll << (i + 1)) + ((1ll << c - 1) - 1);
        }
    }
}

ll G(ll x)
{
    int c = 0;
    ll xt = x;
    for (int i = 0; i < 32; ++i)
    {
        if (x >> i & 1) {
            c ++;
            xt -= (1ll << i);
        }
        if ((x >> i & 1) == 0 && (x >> (i + 1) & 1)) {
            //printf("%lld %d %d\n", x, i, c);
            return xt + (((1ll << (c+1)) - 1) << (i - c)) - (1ll<<i+1);
        }
    }
    return x;
}

int main()
{
  //  freopen("10.in", "r", stdin);
   // freopen("10.out", "w", stdout);
    ll a, b;
    while( scanf("%lld%lld", &a, &b)!=EOF)
    {
        /*assert(__builtin_popcountll(F(a)) == __builtin_popcountll(a));
        assert(__builtin_popcountll(G(a)) == __builtin_popcountll(a));
        assert(__builtin_popcountll(G(b)) == __builtin_popcountll(b));
        assert(__builtin_popcountll(F(b)) == __builtin_popcountll(b));*/
        //assert(__builtin_popcount(1388) == __builtin_popcountll(a));
        ll t1 = F(a) - G(a);
        ll t2 = F(b) - G(b);
        //printf("* %lld %lld %lld %lld\n", F(a), G(a), F(b), G(b));
        if (t1 > t2) puts(">");
        else if (t1 == t2) puts("=");
        else puts("<");
    }
    return 0;
}
