#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 998244353;
ll fac[6000+10];
ll facInv[6000+10];
 
int QuickPow(const ll n, const ll m, ll& res)
{
    ll base = n;
    ll tmp = m;
    res = 1;
    while (tmp)
    {
        if (tmp & 1)
        {
            res *= base;
            res %= mod;
        }
        base *= base;
        base %= mod;
        tmp >>= 1;
    }
    return 1;
}
 
 
void GetFacInv(ll k)
{
    fac[0] = 1;
    facInv[0] = 1;
    for (int i = 1; i <= k; i++)
    {
        fac[i] = ((fac[i-1] * (ll)i) % mod);
        QuickPow(fac[i], mod - 2, facInv[i]);
    }
}
 
 
int main()
{
    GetFacInv(6005);
    int T;
    cin >> T;
    while(T--)
    {
        int n,m;
        cin >> n >> m;
        ll ans = 0;
        for (int k = 1; k <= n; k++)
        {
            for (int t = k*m; t <= n; t++)
            {
                ans += ((((fac[t - k*m + 2*k - 1] * facInv[2*k - 1]) % mod) * facInv[t - k*m]) % mod);
                if (t - k*m >= k) ans -= ((((fac[t - k*m + k - 1] * facInv[2*k - 1]) % mod) * facInv[t - k*m - k]) % mod);
                ans %= mod;
            }
        }
        ans = ((ans % mod) + mod) % mod;
        cout << ans << endl;
    }
}
