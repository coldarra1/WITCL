#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <ctime>
#include <unordered_map>

using namespace std;

#ifndef ONLINE_JUDGE
#include "LocalDebug.h"
#else 
#define dbg(...)
#endif

using LL = long long;

void go () {
	int n, k; cin >> n >> k;
	vector <int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	unordered_map <int,int> ma;
	bool isST = true;
	int use = 0;
	for (int i = 0; i < n; ++i) {
		int x = a[i];
		if (ma[x] > 1) {
			if (!isST) cout << "NO" << "\n"; 
			ma.clear();
			ma[x] = 1;
			use = 1;
			isST = false;
		} else {
			ma[x] = 1;
			use++;
		}
	}
	cout << "YES" << "\n";
}

int main () {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T = 1;
	cin >> T;
	time_t tic = clock();
	while (T--) go();
	time_t toc = clock();
	std::cerr << __FILE__ << " execution time : " << 1000.0 * (toc - tic) / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
