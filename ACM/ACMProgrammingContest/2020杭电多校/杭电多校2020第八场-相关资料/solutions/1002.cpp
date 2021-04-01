#include<bits/stdc++.h>
#define ll long long
using namespace std;
template<typename tn> void read(tn&a){
	tn x=0,f=1;char c=' ';
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	a=x*f;
}
const int inf = 1000000000;
int n,f[1001000],s[1001000],a[1001000],l[1001000],r[1001000],siz[1001000];
vector<int> v[1001000];
int max(int a,int b){return a>b?a:b;}
struct segment_tree{
	int mx[3001000];
	void build(int x=1,int l=0,int r=n){
		if(l==r){mx[x]=-inf;return;}
		int mid=l+r>>1;
		build(x<<1,l,mid);build(x<<1|1,mid+1,r);
		mx[x]=-inf;
	}
	void modify(int w,int k,int x=1,int l=0,int r=n){
		if(l==r){mx[x]=k;return;}
		int mid=l+r>>1;
		if(w<=mid) modify(w,k,x<<1,l,mid);
		else modify(w,k,x<<1|1,mid+1,r);
		mx[x]=max(mx[x<<1],mx[x<<1|1]);
	}
	int query(int ql,int qr,int x=1,int l=0,int r=n){
		if(ql<=l&&qr>=r) return mx[x];
		int mid=l+r>>1,ans=-inf;
		if(ql<=mid) ans=query(ql,qr,x<<1,l,mid);
		if(qr>mid) ans=max(ans,query(ql,qr,x<<1|1,mid+1,r));
		return ans;
	}
}t;
void init()
{
    for (int i=0;i<=n;i++)
        v[i].clear(),f[i]=0,s[i]=0,a[i]=0,l[i]=0,r[i]=0,siz[i]=0;
    
        
}
int main(){
	//freopen("election.in","r",stdin);
  //freopen("1.out","w",stdout);
    int T;
    read(T);
    while(T--)
    {
	int L,R;
	read(n);read(L);read(R);
        init();
	int mn=0;
	for(int i=1;i<=n;i++){
		read(a[i]),s[i]=s[i-1]+a[i];
		mn=min(s[i],mn);
	}
	siz[-mn]=1;
	for(int i=1;i<=n;i++) siz[s[i]-mn]++;
	for(int i=0;i<=n;i++) if(siz[i])v[i].resize(siz[i]+1);
	memset(f,192,sizeof(f));
	f[0]=0;
	t.build();
	for(int i=1;i<=n;i++){
		if(i-L>=0){
			int k=s[i-L]-mn;
			while(l[k]<r[k]&&v[k][r[k]-1]<f[i-L]) r[k]--;
			v[k][r[k]++]=f[i-L];
			if(l[k]==r[k]-1) t.modify(k,v[k][l[k]]);
		}
		if(s[i]-mn>0) f[i]=t.query(0,s[i]-mn-1)+1;
		f[i]=max(f[i],t.query(s[i]-mn+1,n)-1);
		if(l[s[i]-mn]<r[s[i]-mn]) f[i]=max(f[i],v[s[i]-mn][l[s[i]-mn]]);
		if(i-R>=0){
			int k=s[i-R]-mn;
			if(v[k][l[k]]==f[i-R]) l[k]++;
			if(l[k]<r[k]) t.modify(k,v[k][l[k]]);
			else t.modify(k,-inf);
		}
	}
	if(f[n]<-n) cout<<"Impossible\n";
	else cout<<f[n]<<'\n';
    }
	return 0;
}
