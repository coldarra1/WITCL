#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int M = 62;
const int N = 200010;
ll a[M], res[M + 10], p[N * 2], q[N * 2], b[M];
void add(ll x){
	per(i, 0, M){
		if(x >> i & 1){
			if(a[i]) x ^= a[i];
			else {
				a[i] = x;
				break;
			}
		}
	}
}
bool check(ll x){
	per(i, 0, M){
		if(x >> i & 1){
			if(a[i]) x ^= a[i];
			else return x;
		}
	}
	return x;
}
ll solve(ll x){
	ll ans = 0;
	per(i, 0, M){
		if(x >> i & 1){
			x ^= a[i];
			ans ^= res[i];
		}
	}
	return ans;
}
ll get(string s){
	ll res = 0;
	rep(i, 0, s.size()) res = res * 10 + s[i] - '0';
	return res;
}
bool doit(int n, int cnt){
	int pos = 0, pos1 = 0, sum1 = 0, sum2 = 0;
	per(i, 0, M){
		rep(j, pos + 1, n) {
			if(p[j] >> i & 1){
				swap(p[j], p[pos]);
				swap(q[j], q[pos]);
				break;
			}
		}
		if(p[pos] >> i & 1) {
			res[pos] = q[pos];
			rep(j, pos + 1, n) {
				if(p[j] & p[pos] & (1ll << i)){
					p[j] ^= p[pos];
					q[j] ^= q[pos];
				}
			}
			pos ++;
		}
	}
	rep(i, pos, n) if(q[i]) return true;
	per(i, 0, M){
		rep(j, pos1 + 1, pos) {
			if(q[j] >> i & 1){
				swap(p[j], p[pos1]);
				swap(q[j], q[pos1]);
				break;
			}
		}
		if(q[pos1] >> i & 1) {
			rep(j, pos1 + 1, pos) {
				if(q[j] & q[pos1] & (1ll << i)){
					p[j] ^= p[pos1];
					q[j] ^= q[pos1];
				}
			}
			pos1++;
		}
	}
	rep(i, 0, pos) {
		if(q[i] == 1) sum1 ++;
		if(q[i] == 0) sum2 ++;
	}
	if(sum1 > cnt / 2 || sum2 > cnt / 2) return true;
	return false;
}
void init(){
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));
	memset(res, 0, sizeof(res));
}
void cal(){
	init();
	int n;
	cin >> n;
	rep(i, 1, n + 1) {
		ll x;
		cin >> x;
		add(x);
	}
	int cnt = 0;
	ll last = -1;
	rep(i, 0, M){
		if(a[i]) {
			cnt ++;
			if(cnt % 2 == 0){
				res[i] = last;
			}
			else last = a[i];
		}
	}
	string op;
	cin >> op;
	if(op == "construct"){
		int flag = 0;
		if(cnt % 2 == 1){
			cout << "NoSolution" << endl;
			flag = 1;
		}
		else cout << "HaveSolution" << endl;
		int m;
		cin >> m;
		while(m --){
			ll x;
			cin >> x;
			if(flag) continue;
			if(check(x)){
				cout << "-1" << endl;
			}
			else{
				cout << solve(x) << endl;
			}
		}
	}
	else{
		string s;
		cin >> s;
		int flag = 1;
		if(cnt % 2 == 1) flag = 0;
		if(s == "NoSolution") {
			if(cnt % 2 == 1){
				cout << "Yes" << endl;
			}
			else{
				cout << "No" << endl;
			}
			return ;
		}
		int m;
		cin >> m;
		memset(res, -1, sizeof(res));
		int num = 0;
		while(m --){
			ll x;
			string y;
			cin >> x >> y;
			if(y == "-1"){
				if(!check(x)) flag = 0;
			}
			else {
				ll z = get(y);
				if(check(x) || check(z)) flag = 0;
				p[num] = x;
				q[num] = z;
				num ++;
				if(z) {
					p[num] = z;
					q[num] = 0;
					num ++;
				}
			}
		}
		if(doit(num, cnt)) flag = 0;
		if(flag){
			cout << "Yes" << endl;
		}
		else{
			cout << "No" << endl;
		}
		rep(i, 0, num) q[i] = p[i] = 0;
	}

}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	int T;
	cin >> T;
	while(T --) cal();
	return 0;
}