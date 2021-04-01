#include<bits/stdc++.h>
using namespace std;
int main(){
	int T; scanf("%d",&T);
	while (T--){
		int a, b, c, d;
		scanf("%d%d%d%d", &a, &b, &c, &d);
		puts(max(b,c) >= max(a,d)?"AB//CD":"AB//DC");
	}
}