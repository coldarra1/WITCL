#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int f0[N], f1[N], g0[N], g1[N], a[N], c[N], id[N], n;
struct Pair{
	int x, y;
	Pair(){}
	Pair(int _x, int _y){
		x = _x;
		y = _y;
	}
	Pair add(int z){
		int nowx = x, nowy = y;
		if (z == 0){
			if (!nowy) nowx++; else nowy--;
		}
		else{
			++nowy;
			if (nowy >= 3) nowy -= 2;
		}
		return Pair(nowx, nowy);
	}
	int operator == (const Pair &b){
		return x == b.x && y == b.y;
	}
}sum[N];
int cmp(int A, int B){
	return a[A] < a[B];
}
void read(int &x){
    char ch=getchar();x=0;
    for (;ch<'0';ch=getchar());
    for (;ch>='0';ch=getchar()) x=x*10+ch-'0';
}
void solve(int *f){
	static int id[N], c[N], num[N];
	for (int i = 1; i <= n; i++) id[i] = i;
	sort(id + 1, id + n + 1, cmp);
	sum[0] = Pair(0, 0);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i-1].add(num[i] = 1);
	for (int i = 1; i <= n; i++) c[i] = 0;
	int okline = n+1;
	for (int i = 1; i <= n; i++){
		int pos = id[i], smaller = 0;
		for (int k = pos; k; k -= k&-k) smaller += c[k];
		
		f[pos] |= 1 * (smaller <= pos - 1 - smaller) * (sum[pos-1].x >= sum[pos-1].y || pos >= okline);
		f[pos] |= 2 * (sum[pos-1].x > sum[pos-1].y || pos >= okline);
		
		num[pos] = 0; //now change (pos) to 0.
		for (int j = pos; j <= n; j++){
			Pair last = sum[j];
			sum[j] = sum[j-1].add(num[j]);
			if (sum[j].x >= 3){
				okline = min(okline, j);
				break;
			}
			if (sum[j] == last) break;
		}
		for (int k = pos; k <= n; k += k&-k) c[k] ++;
		//for (int j = 1; j <= n; j++) printf("%d%c", num[j], j==n?'\n':' ');
		//for (int j = 1; j <= n; j++) printf("(%d,%d)%c", sum[j].x, sum[j].y, j==n?'\n':' ');
	}
	//for (int i = 1; i <= n; i++) printf("%d%c",f[i], i==n?'\n':' ');puts("");
}
int main(){
	int T; read(T);
	while (T--){
		read(n);
		for (int i = 1; i <= n; i++)
			read(a[i]);
		for (int i = 1; i <= n; i++)
			f0[i] = f1[i] = g0[i] = g1[i] = 0;
		
		solve(f0);
		for (int i = 1; i <= n; i++)
			a[i] = -a[i];
		solve(f1);
		reverse(a + 1, a + n + 1);
		solve(g1);
		for (int i = 1; i <= n; i++)
			a[i] = -a[i];
		solve(g0);
		
		for (int i = 1; i <= n; i++){
			int ok = 0;
			//printf("%d %d %d %d %d\n",i, f0[i-1], f1[i-1], g0[n-i], g1[n-i]);
			ok |= (f0[i] & 2) && (g1[n-i+1] & 2);
			ok |= (f1[i] & 2) && (g0[n-i+1] & 2);
		    ok |= ((f0[i]|f1[i]) & 1) && ((g0[n-i+1]|g1[n-i+1]) & 1) && (i & 1);
		    putchar(ok ? '1' : '0');
		}
		
		puts("");
	}
}