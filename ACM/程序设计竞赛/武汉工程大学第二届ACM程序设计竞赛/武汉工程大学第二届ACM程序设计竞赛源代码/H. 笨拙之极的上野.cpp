#include<iostream>
#include<cstdio>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
 
using namespace std;
typedef long long ll;
 
int main()
{
	set<ll>a, b;
	map<ll, ll>mp_x;
	map<ll, vector<ll>>mp_y;
	ll m;
	cin >> m;
	while (m--) {
		string op;
		cin >> op;
		if (op[0] == 'a' && op[3] == 'A') {
			ll x = 0;
			if(op[5]=='-'){
				for (int i = 6; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					x = x * 10 + digit;
				}
				a.insert(-x);
			}else{
				for (int i = 5; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					x = x * 10 + digit;
				}
				a.insert(x);
			}
		}
		else if (op[0] == 'a' && op[3] == 'B') {
			ll x = 0;
			if(op[5]=='-'){
				for (int i = 6; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					x = x * 10 + digit;
				}
				b.insert(-x);
			}else{
				for (int i = 5; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					x = x * 10 + digit;
				}
				b.insert(x);
			}
		}
		else if (op[0] == 'b') {
			int p = 9;
			int sign=1;
			ll x = 0, y = 0;
			if(op[p]=='-'){
				sign=-1;
				++p;
			}
			while (op[p] != ',') {
				ll digit = op[p] - '0';
				x = x * 10 + digit;
				++p;
			}
			x=sign*x;
			if(op[p+1]=='-'){
				for (int i = p+2; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					y = y * 10 + digit;
				}
				y=-y;
			}else{
				for (int i = p+1; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					y = y * 10 + digit;
				}
			}
			if (a.count(x) == 0 && b.count(y) == 1) {
				cout << "Invalid!Can't find x." << endl;
			}
			else if (a.count(x) == 1 && b.count(y) == 0) {
				if (!mp_x.count(x)) 
					cout << "Invalid!Can't find y." << endl;
				else
					printf("Invalid!There is already a map from %lld.\n", x);
			}
			else if (a.count(x) == 0 && b.count(y) == 0) {
				cout << "Invalid!Can't find both x and y." << endl;
			}
			else {
				if (mp_x.count(x))
					printf("Invalid!There is already a map from %lld.\n", x);
				else {
					mp_x[x] = y;
					mp_y[y].push_back(x);
				}
			}
		}
		else if (op[0] == 'f' && op[4] == 'y') {
			ll x = 0;
			if(op[6]=='-'){
				for (int i = 7; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					x = x * 10 + digit;
				}
				x=-x;
			}else{
				for (int i = 6; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					x = x * 10 + digit;
				}
			}
			auto search = mp_x.find(x);
			if (search != mp_x.end()) {
				cout << search->second << endl;
			}
			else {
				cout << "Invalid!No such map." << endl;
			}
		}
		else if (op[0] == 'f' && op[4] == 'x') {
			ll x = 0;
			if(op[6]=='-'){
				for (int i = 7; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					x = x * 10 + digit;
				}
				x=-x;
			}else{
				for (int i = 6; i < op.size() - 1; ++i) {
					int digit = op[i] - '0';
					x = x * 10 + digit;
				}
			}
			auto search = mp_y.find(x);
			if (search != mp_y.end()) {
				sort(search->second.begin(), search->second.end());
				for (int i = 0; i < search->second.size(); i++)
					printf("%lld%c", search->second[i], " \n"[i + 1 == search->second.size()]);
			}
			else {
				cout << "Invalid!No such map." << endl;
			}
		}
	}
	return 0;
}
