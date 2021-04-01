#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 100010;

struct robot{
	int p, a;
	robot(int p = 0, int a = 0) : p(p), a(a){}
	bool operator<(const robot& ar) const { return p == ar.p ? a > ar.a : p > ar.p; }
	bool operator==(const robot& ar) const { return p == ar.p && a == ar.a; }
}rbt[N];

int ids[N];

int flag1[N], flag2[N];

int stks[N];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int T; cin >> T;
	
	for(int t = 1; t <= T; t++){
		int n; cin >> n;
		for(int i = 0; i < n; i++)
			cin >> rbt[i].p >> rbt[i].a;
		
		sort(rbt, rbt + n);
		for(int i = 0; i < n - 1; i++)
			if(rbt[i] == rbt[i + 1])
				flag1[i] = flag1[i + 1] = t;
		
		int nn = 0;
		for(int i = 0; i < n; i++)
			if(nn == 0 || rbt[i].a > rbt[ids[nn - 1]].a)
				ids[nn++] = i;
		for(int i = 0; i < nn; i++)
			if(flag1[ids[i]] == t)
				flag2[i] = t;
		n = nn;
		for(int i = 0; i < n; i++)
			rbt[i] = rbt[ids[i]];
		
		int ans = 0;
		stks[ans++] = 0;
		if(n > 1) stks[ans++] = 1;
		
		for(int i = 2; i < n; i++){
			while(ans >= 2){
				int id1 = stks[ans - 1], id2 = stks[ans - 2];
				int dpos1 = rbt[id1].p - rbt[i].p, dpos2 = rbt[id2].p - rbt[id1].p;
				int da1 = rbt[i].a - rbt[id1].a, da2 = rbt[id1].a - rbt[id2].a;
				if((ll)dpos1 * da2 > (ll)da1 * dpos2) break;
				ans--;
			}
			stks[ans++] = i;
		}
		
		int res = ans;
		for(int i = 0; i < ans; i++)
			if(flag2[stks[i]] == t)
				res--;
		cout << res << "\n";
	}
	
	return 0;
}
