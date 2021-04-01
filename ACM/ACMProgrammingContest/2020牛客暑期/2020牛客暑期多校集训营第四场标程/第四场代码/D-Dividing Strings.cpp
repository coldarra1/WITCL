#include<bits/stdc++.h>
#define N 200005
using namespace std;
int a[N],n; char s[N];
int bigger(int *a, int *b, int l){
	for (int i=0;i<l;i++)
		if (a[i]!=b[i]) return a[i]>b[i];
	return 0;
}
void copy(int *a, int *b, int l){
	for (int i=0;i<l;i++) a[i]=b[i];
}
int force(int len){
	int _min[len],_max[len];
	for (int i=1;i<=len;i++)
		_min[i-1]=_max[i-1]=a[i];
	for (int i=len+1;i<=n;i+=len){
		if (a[i]==0) return 9;
		if (bigger(a+i, _max, len))
			copy(_max, a+i, len);
		if (bigger(_min, a+i, len))
			copy(_min, a+i, len);
	}
	int now=9;
	for (int i=len-1;i>=0;i--){
		int t=_max[i]-_min[i];
		if (t<0) t+=10,_max[i-1]--;
		if (i==len-1) now=t;
		else if (t>0) return 9;
	}
	return now;
}
int find_need(){
	for (int i=1;i<=n;i++)
		if (a[i]==1){
			int len=i;
			while (len<n&&a[len+1]==0) ++len;
			if (len<n&&a[len+1]<9) ++len;
			return len-i;
		}
	return -1;
}
int doit(int need){
	int len=1,big=0,small=9;
	for (int k=1;k<=n;){
		int last=k;
		if (a[k]==1){
			while (k<n&&a[k+1]==0) ++k;
			if (k<n&&a[k+1]<9&&k-last+1<need+1) ++k;
			if (k-last+1!=need+1) return 9;
			big=max(big,a[k]);++k;
		}
		else{
			k--;
			while (k<n&&a[k+1]==9&&k-last+1<need) ++k;
			if (k<n&&a[k+1]<9&&k-last+1<need) ++k;
			if (k-last+1!=need) return 9;
			small=min(small,a[k]);++k;
		}
	}
	return big+10-small;
}
int main(){
	int T; scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		scanf("%s",s+1);
		for (int i=1;i<=n;i++) a[i]=s[i]-'0';
		int _min=a[1],_max=a[1];
		for (int i=1;i<=n;i++)
			_min=min(_min,a[i]),_max=max(_max,a[i]);
		int ans=_max-_min;
		for (int len=1;len<n;len++)
			if (n%len==0)
				ans=min(ans,force(len));
		int need=find_need();
		if (need!=-1){
			if (need>0) ans=min(ans,doit(need));
			if (need>1) ans=min(ans,doit(need-1));
		}
		printf("%d\n",ans);
	}
}