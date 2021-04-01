#include<bits/stdc++.h>
#define dd(x) cout<<#x<<" = "<<x<<" "
#define de(x) cout<<#x<<" = "<<x<<endl
#define sz(x) int(x.size())
#define All(x) x.begin(),x.end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> P;
const double eps=1e-8;
inline int sign(double x){return (x>eps)-(x<-eps);}
const int maxn=1e6+10,mod=1e9+7,INF=0x3f3f3f3f;
int s[maxn];
int sa[maxn], rk[maxn], height[maxn], c[maxn], y[maxn];
int mn[maxn][22],lg[maxn];
inline int qry(int l,int r){
	int k=lg[r-l+1];
	return min(mn[l][k],mn[r-(1<<k)+1][k]);
}
inline int lcp(int i,int j){
	if (i>j) swap(i, j);
	return qry(i+1,j);
}
void getSA(int n,int m){
	for (int i = 0; i <= m; i++) c[i] = 0;
	for (int i = 1; i <= n; i++) c[rk[i]=s[i]]++;
	for (int i = 1; i <= m; i++) c[i] += c[i - 1];
	for (int i = n; i; i--) sa[c[rk[i]]--] = i;
	for (int k = 1, p; k <= n; k <<= 1) {
		p = 0;
		for (int i = n; i > n - k; i--) y[++p] = i;
		for (int i = 1; i <= n; i++)
			if (sa[i] > k) y[++p] = sa[i] - k;
		for (int i = 0; i <= m; i++) c[i] = 0;
		for (int i = 1; i <= n; i++) c[rk[i]]++;
		for (int i = 1; i <= m; i++) c[i] += c[i - 1];
		for (int i = n; i; i--) sa[c[rk[y[i]]]--] = y[i];
		p = y[sa[1]] = 1;
		for (int i = 2, a, b; i <= n; i++) {
			a = sa[i] + k > n ? -1 : rk[sa[i] + k];
			b = sa[i - 1] + k > n ? -1 : rk[sa[i - 1] + k];
			y[sa[i]] = (rk[sa[i]] == rk[sa[i - 1]]) && (a == b) ? p : ++p;
		}
		swap(rk, y);
		m = p;
	}
	int k=0;
	for (int i=1;i<=n;++i){
		if (k) k--;
		int j=sa[rk[i]-1];
		while (s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;
	}	
	for (int i=2;i<=n;++i)
		lg[i]=lg[i-1]+((i&-i)==i);
	for (int i=1;i<=n;++i)
		mn[i][0]=height[i];
	for (int j=1;(1<<j)<=n;++j)
		for (int i=1;i+(1<<j)-1<=n;++i)
			mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);	
}

int id,rt[maxn],ls[maxn*22],rs[maxn*22],cnt[maxn*22];
void upd(int pre,int& now,int c,int l,int r){
	now=++id;
	cnt[now]=cnt[pre]+1;
	ls[now]=ls[pre],rs[now]=rs[pre];
	if (l==r)	return;
	int m=l+r>>1;
	if (c<=m)	upd(ls[pre],ls[now],c,l,m);
	else	upd(rs[pre],rs[now],c,m+1,r);
}
int qry(int now,int k,int l,int r){
	if (l==r)
		return cnt[now];
	int m=l+r>>1;
	if (k>m)
		return cnt[ls[now]]+qry(rs[now],k-cnt[ls[now]],m+1,r);
	return qry(ls[now],k,l,m);
}

int ne[maxn];
void build(int n,int m){
	reverse(s+1,s+1+n);
	ne[1]=0;
	for (int i=2,j=0;i<=n;++i){
		while (s[j+1]!=s[i]&&j)
			j=ne[j];
		if (s[j+1]==s[i])
			++j;
		ne[i]=j;
		if (ne[i])
			upd(rt[ne[i]],rt[i],s[i-ne[i]],1,m);
	}
	reverse(s+1,s+1+n);
}

inline int cal1(int c,int p,int n){
	int l=rk[p]+1,r=n,pos=rk[p];
	while (l<=r){
		int mid=l+r>>1,len=n-p+1;
		if (lcp(rk[p],mid)==len&&s[sa[mid]+len]<c)
			l=mid+1,pos=mid;
		else
			r=mid-1;
	}
	return pos-rk[p];
}
inline int cal2(int c,int p,int n,int m){
	return c==1?0:qry(rt[n-p+1],c-1,1,m);
}
inline int getrk(int c,int n){
    rk[n+1]=0;
	int l=1,r=n,pos=0;
	while (l<=r){
		int mid=l+r>>1;
		if (s[sa[mid]]<c||(s[sa[mid]]==c&&rk[sa[mid]+1]<rk[1]))
			l=mid+1,pos=mid;
		else
			r=mid-1;
	}
	return pos+1;
}
int num[maxn];
void init(int n,int m){
	id=0;
	for (int i=1;i<=n;++i)	rt[i]=0;
	for (int i=1;i<=m;++i)	num[i]=0;
}
int main()
{
	int T;
	cin>>T;
	while (T--){
		int n,m,q;
		cin>>n>>m>>q;
		init(n,m);
		for (int i=1;i<=n;++i){ 
			scanf("%d",&s[i]);
			num[s[i]]++;
		}
		for (int i=1;i<=m;++i)	num[i]+=num[i-1];
		getSA(n,m);
		build(n,m); 
		int last=0;
		while (q--){
			int op,c,p;
			scanf("%d%d%d",&op,&c,&p);
			c^=last;
			p^=last;
			if (op==1){
				int pos=getrk(c,n);
				if (p==1)
					last=pos;
				else
					last=rk[p-1]+(pos<=rk[p-1]);
			}
			else{
				if (p==n+1)
					last=num[c-1]+1;
				else
					last=rk[p]+cal1(c,p,n)-cal2(c,p,n,m)+(c<=s[p]);
			}
			printf("%d\n",last);
		}
	}
	return 0;
}

