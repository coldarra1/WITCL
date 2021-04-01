#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
typedef double db;
mt19937 mrand(random_device{}()); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=1010000;
int _,p,vis[N];
int main() {
	for (scanf("%d",&_);_;_--) {
		scanf("%d",&p);
		for (int i=1;i<p;i++) vis[i]=0; vis[0]=1;
		VI ret;
		int x=1;
		while (1) {
			vis[x]=1; ret.pb(x);
			if (!vis[x*2%p]) x=x*2%p;
			else if (!vis[x*3%p]) x=x*3%p;
			else break;
		}
		if (SZ(ret)!=p-1) {
			puts("-1");
		} else {
			rep(i,0,SZ(ret)) printf("%d%c",ret[i]," \n"[i==p-2]);
		}
	}
}