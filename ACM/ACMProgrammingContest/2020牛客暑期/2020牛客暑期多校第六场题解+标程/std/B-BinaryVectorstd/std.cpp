#include <bits/stdc++.h>

const int maxn = 20000111;
const int mod = 1e9 + 7;

int ans[maxn], p2[maxn], ip2[maxn];
int main()
{
    p2[0] = ip2[0] = 1;
    ans[0] = 1;
    for(int i=1; i<maxn; i++)
    {
        p2[i] = p2[i-1] * 2ll % mod;
        ip2[i] = ip2[i-1] * 1ll * (mod + 1) / 2 % mod;
        ans[i] = 1ll * ans[i-1] * ip2[i] % mod * (p2[i] - 1) % mod;
    }
	for(int i=2; i<maxn; i++) ans[i] ^= ans[i-1];
    int tc;
    scanf("%d", &tc);
    while(tc--)
    {
        int x;
        scanf("%d", &x);
        printf("%d\n", ans[x]);
    }
    return 0;
}