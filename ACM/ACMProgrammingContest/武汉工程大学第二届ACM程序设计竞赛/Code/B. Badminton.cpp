# include <iostream>
# include <algorithm>
 
using namespace std;
 
typedef long long LL;
const int maxn = 1010;
LL F[maxn];
 
int main()
{
	LL n, h;
	cin >> n >> h;
	for (int i = 0; i < n; i++) {
		LL v, s;
		cin >> v >> s;
		for (int j = h; j >= v; j--)
			F[j] = max(F[j], F[j - v] + s);
	}
	cout << F[h] << endl;
	return 0;
}
