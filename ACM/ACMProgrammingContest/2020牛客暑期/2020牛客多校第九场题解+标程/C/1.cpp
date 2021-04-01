#include <bits/stdc++.h>
using namespace std;
#define M 500005
typedef long long LL;
template<class T>bool tomax(T &x,T y){
	if(x<y)return x=y,1;
	return 0;
}
template<class T>bool tomin(T &x,T y){
	if(y<x)return x=y,1;
	return 0; 
} 
template<class T>void Rd(T &x){
	static char c;
	while(c=getchar(),!isdigit(c));
	for(x=0;isdigit(c);c=getchar())
		x=(x<<1)+(x<<3)+(c^48); 
}
int n;
pair<int,int> A[M];
const int P=998244353;
void Mul(int &x,int y){
	x=1LL*x*y%P;
}
int qikpow(int a,int b){
	int ret=1;
	for(;b;b>>=1,Mul(a,a))
		if(b&1)Mul(ret,a);
	return ret;
}
#define calc(x,y) x=((y)+(x))%P
int Num[M<<1],m,Pw[M],V[M<<1],dif[M<<1];
vector<int>Q[M<<1];
struct YD{
	struct TNode{
		int l,r,mul,s;
		void Reset(){Mul(mul,2),Mul(s,2);}
	}tree[M<<3];
	#define fa tree[p]
	void Up(int p){fa.s=1LL*fa.mul*(tree[p<<1].s+tree[p<<1|1].s)%P;}
	void build(int l,int r,int p){
		fa.l=l,fa.r=r,fa.mul=1,fa.s=0;
		if(l==r)return void(fa.s=V[l]);
		int mid=l+r>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		Up(p);
	}
	void Update(int l,int r,int p){
		if(l==fa.l&&r==fa.r)return void(fa.Reset());
		int mid=fa.l+fa.r>>1;
		if(r<=mid)Update(l,r,p<<1);
		else if(l>mid)Update(l,r,p<<1|1);
		else Update(l,mid,p<<1),Update(mid+1,r,p<<1|1);
		Up(p);
	}
	int Query(int x){
		int p=1,ret=0,mul=1;
		while(fa.l^fa.r){
			int mid=fa.l+fa.r>>1;
			Mul(mul,fa.mul);
			if(x<=mid)calc(ret,1LL*mul*tree[p<<1|1].s),p<<=1;
			else p=p<<1|1;
		}
		return (1LL*mul*fa.s+ret)%P;
	}
	#undef fa
}T;
int main(){
	Rd(n);
	for(int i=1;i<=n;i++){
		Rd(A[i].first),Rd(A[i].second),A[i].second++;
		Num[++m]=A[i].first,Num[++m]=A[i].second;
	}
	Pw[0]=1;
	for(int i=1;i<=n;i++)Pw[i]=2LL*Pw[i-1]%P;
	sort(Num+1,Num+1+m);
	m=unique(Num+1,Num+1+m)-Num-1;
	for(int i=1;i<=n;i++){
		A[i].first=lower_bound(Num+1,Num+1+m,A[i].first)-Num;
		A[i].second=lower_bound(Num+1,Num+1+m,A[i].second)-Num-1;
		Q[A[i].first].push_back(A[i].second);
		dif[A[i].first]++,dif[A[i].second+1]--;
	}
	for(int i=1;i<m;i++)V[i]=Num[i+1]-Num[i],dif[i]+=dif[i-1];
	T.build(1,m-1,1);
	int ans=0;
	for(int l=1;l<m;l++){
		for(int i=0;i<Q[l].size();i++){
			int r=Q[l][i];
			T.Update(l,r,1);
		}
		calc(ans,1LL*V[l]*(2LL*P+T.Query(l)-Num[m]+Num[l]));
	}
	Mul(ans,2);
	for(int i=1;i<m;i++)
		calc(ans,P-1LL*(Pw[dif[i]]-1)*V[i]%P*V[i]%P);
	cout<<1LL*ans*qikpow(Pw[n],P-2)%P;
	return 0;
}
