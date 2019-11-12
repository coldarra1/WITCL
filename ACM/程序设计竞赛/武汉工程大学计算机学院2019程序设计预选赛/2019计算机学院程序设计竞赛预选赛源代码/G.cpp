# include <iostream>	// NQ
# include <cstdio>
# include <algorithm>

using namespace std;

const int N = 1010, mod = 1e9 + 7;
int n, m, nums[N];

int main()
{
	scanf("%d %d", &n, &m);
	nums[0] = 1;
	while (n--) {
		int v;
		scanf("%d", &v);
		for (int i = m; i >= v; i--)
			nums[i] = (nums[i] + nums[i - v]) % mod;
	}
	cout << nums[m] << endl;
	return 0;
}
