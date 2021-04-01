#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
int sqr;
bool isp[100000];
int p[100000];
int tot = 0;
 
ll zh[100000]; ///zh[i][k]ŒÇÂŒ(p[1])^k + (p[2])^k + ... + (p[i])^k
ll g[100000];
 
void sieve(int mm)
{
    memset(isp,1,sizeof isp);
    isp[1] = 0;
    tot = 0;
    for(int i=2;i<=mm;i++){
        if(isp[i])
        {
            p[++tot] = i;
            //if(i==2) zh[tot] = 0;
            zh[tot] = zh[tot-1] + ((i%4==1)?4:1);
        }
        for(int j=1;i*p[j]<=mm&&j<=tot;j++){
            isp[i*p[j]] = 0;
            if(i%p[j]==0) break;
        }
    }
}
ll S1[100000][10];
ll S2[100000][10];
 
ll h1[100000];
ll h2[100000];
/**ÖÊÊýŽŠµÄÐÅÏ¢**/
 
 
void gogogo(ll n,int m)
{
    for(ll i=1;i<=n;){
        if(i<=sqr) for(int j=0;j<m;j++) S1[i][j] = (i-1)/m + ((((i-1)%m+1)>=((j+m-1)%m+1))?1:0);
        else for(int j=0;j<m;j++) S2[n/i][j] = (i-1)/m + ((((i-1)%m+1)>=((j+m-1)%m+1))?1:0);
        if(i==n) break;
        i = n/(n/(i+1));
    }
    for(int i=1;i<=tot;i++)
    {
        int p = ::p[i];
        ll p2 = p*p;
        for(ll a=n;a>=p2;){
            for(int j=0;j<m;j++){
                if(a<=sqr){
                    if(a/p<=sqr) S1[a][p*j%m] -= S1[a/p][j] - S1[p-1][j];
                    else S1[a][p*j%m] -= S2[n/(a/p)][j] - S1[p-1][j];
                }
                else{
                    if(a/p<=sqr) S2[n/a][p*j%m] -= S1[a/p][j] - S1[p-1][j];
                    else S2[n/a][p*j%m] -= S2[n/(a/p)][j] - S1[p-1][j];
                }
            }
            a = n/(n/a+1);
        }
    }
    for(int i=1;i<=n;){
        if(i<=sqr) S1[i][1]-= 1;
        else S2[n/i][1] -= 1;
        if(i==n) break;
        i = n/(n/(i+1));
    }
 
    for(int i=1;i<=n;){
        if(i<=sqr) h1[i] = S1[i][1]*4 + S1[i][3] + 1;
        else h2[n/i] = S2[n/i][1]*4 + S2[n/i][3] + 1;
        if(i==n) break;
        i = n/(n/(i+1));
    }
 
}
 
ll f(ll p,ll k) ///ŒÆËãf(p^k)ŽŠµÄÖµ
{
    if(p%4==1) return 3*k+1;
    else if(p%4==3) return 1;
    return 1;
}
 
 
 
ll get_s(ll x,int k)
{
    if(x<=1||p[k]>x) return 0;
    ll ans = 0;
    if(x<=sqr) ans = h1[x];
    else ans = h2[n/x];
    ans -= zh[k-1];
    for(int i=k;i<=tot&&1LL*p[i]*p[i]<=x;++i)
    {
        for(ll l=p[i],e=1;l*p[i]<=x;l=l*p[i],++e)
        {
            ans = ans + (get_s(x/l,i+1)*f(p[i],e))+f(p[i],e+1);
        }
    }
    return ans;
 
}
 
int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        cin >> n;
        sqr = (int)sqrt(n);
        sieve(sqr);
        gogogo(n,4);
 
        cout << get_s(n,1) + 1 << endl;
 
    }
}
