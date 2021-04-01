#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int a[N],b[N],num[N],n,tot,Case;
vector<int>e[N],app[N],can;

int ch[N],sum[N];
set<pair<int,int> >S[2];
void Color(vector<int>be,int around){
	static int sum[N];
	static vector<int>st;st.clear();st.push_back(around);
	sum[0]=be[0];S[0].clear();S[1].clear();
	for (int i=1;i<be.size();i++){
		sum[i]=sum[i-1]+(be[i]>0);
		if (be[i]>0) S[i&1].insert(make_pair(i-2*sum[i-1],i));
	}
	++Case;
	for (int i=0;i<be.size();i++)
		if (be[i]>0){
			if (st.size()>1&&st[st.size()-2]==be[i])
				st.pop_back();
			else st.push_back(be[i]);
		}
		else {
			//j>i  (Sum_{j-1}-Sum_i)*2=j-i  i-2*Sum[i] = j-2*Sum[j-1]
			int j=be.size();
			while (true){
				auto it=S[i&1].lower_bound(make_pair(i-2*sum[i],0));
				if (it==S[i&1].end()||(*it).first!=i-2*sum[i]) break;
				if ((*it).second<=i) S[i&1].erase(it);
				else {j=(*it).second;break;}
			}
			if (j<be.size()){
				a[-be[i]]=be[j];
				if (ch[be[j]]==Case){
					while (st.back()!=be[j]) st.pop_back();
				}
				else ch[be[j]]=Case,st.push_back(be[j]);
			}
			else {
				if (st.size()>1){
					a[-be[i]]=st[st.size()-2];
					st.pop_back();
				}
				else{
					assert(can.size());
					st.push_back(a[-be[i]]=can.back());
					can.pop_back();
				}
			}
		}
}
void solve(int l,int r,int around){
	if (l>r) return;
	vector<int>be;
	for (int i=l;i<=r;i++)
		if (a[i]==-1) be.push_back(-i);
		else {
			for (int k=0;k+1<app[a[i]].size();k++)
				solve(app[a[i]][k]+1,app[a[i]][k+1]-1,a[i]);
			be.push_back(a[i]);
			i=app[a[i]].back();
		}
	Color(be,around);
}
void euler(int x){
	b[++tot]=x;
	for (int i=0;i<e[x].size();i++)
		euler(e[x][i]),b[++tot]=x;
}
void read(int &x){
	char ch=getchar();x=0;int f=1;
	for (;ch<'0';ch=getchar()) if (ch=='-') f=-1;
	for (;ch>='0';ch=getchar()) x=x*10+ch-'0';x*=f;
}
void Print(int x){
	static int Q[20];*Q=0;
	for (;x;x/=10) Q[++*Q]=x%10;
	for (int i=*Q;i;--i) putchar('0'+Q[i]);
}
int main(){
	int sumN=0;
	int T;read(T);
	while (T--){
		read(n);sumN+=n;
		for (int i=1;i<2*n;i++) read(a[i]);
		a[1]=a[2*n-1]=1;
		for (int i=1;i<=n;i++) app[i].clear();can.clear();
		for (int i=1;i<2*n;i++)
			if (a[i]!=-1) app[a[i]].push_back(i);
		for (int i=1;i<=n;i++)
			if (!app[i].size()) can.push_back(i);
		for (int k=0;k+1<app[1].size();k++)
			solve(app[1][k]+1,app[1][k+1]-1,1);
		for (int i=1;i<2*n;i++)
			Print(a[i]),putchar(i==2*n-1?'\n':' ');
	}
	//fprintf(stderr,"%d\n",sumN);
}
