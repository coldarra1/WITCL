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
mt19937_64 mrand(random_device{}()); 
const ll mod=1000000007;
int rnd(int x) { return mrand() % x;}
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}
// head

const int N=2200000;
int d,cnt[N],dif[N];
vector<PII> v1[30],v2[30];
char s[N],t[N];
int main() {
	scanf("%d",&d);
	scanf("%s%s",s,t);
	int n=strlen(s),m=strlen(t);
	int d1=0,d2=0;
	rep(i,0,n-d) d1+=s[i]!=s[i+d];
	rep(i,0,m-d) d2+=t[i]!=t[i+d];
	fprintf(stderr,"%d %d\n",d1,d2);
	reverse(t,t+m);
	rep(i,0,d) v1[s[i]-'a'].pb(mp(i-d,-1)),v2[t[i]-'a'].pb(mp(i-d,-1));
	rep(i,0,n) if (s[i]!=s[i+d]) {
		v1[s[i]-'a'].pb(mp(i,1));
		if (i+d<n) v1[s[i+d]-'a'].pb(mp(i,-1));
	}
	rep(i,0,m) if (t[i]!=t[i+d]) {
		v2[t[i]-'a'].pb(mp(i,1));
		if (i+d<m) v2[t[i+d]-'a'].pb(mp(i,-1));
	}
	/*
	rep(i,0,26) {
		for (auto p:v1[i]) {
			printf("s %d %d %d\n",i,p.fi,p.se);
		}
	}
	rep(i,0,26) {
		for (auto p:v2[i]) {
			printf("t %d %d %d\n",i,p.fi,p.se);
		}
	}*/
	rep(i,0,26) for (auto p:v1[i]) for (auto q:v2[i]) {
		if (p.fi+q.fi>=m-1) cnt[p.fi+q.fi]+=p.se*q.se;
	}
	//rep(i,0,n+m) printf("%d ",cnt[i]);
	//puts("");
	per(i,m-1,n+m) {
		dif[i]=cnt[i]+2*dif[i+d]-dif[i+2*d];
		//printf("%d %d\n",i,dif[i]);
	}

	rep(i,0,n-m+1) printf("%d\n",m-dif[i+m-1]);
}