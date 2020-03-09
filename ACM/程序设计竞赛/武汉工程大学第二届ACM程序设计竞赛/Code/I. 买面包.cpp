# include <iostream>
# include <cstdio>
# include <vector>
# include <algorithm>
     
using namespace std;
     
typedef long long LL;
const int maxn = (2e5 + 5) * 2;
int pos;
int cnt_prime_numbers[maxn], prime[maxn];
bool vis[maxn];
     
void get_prime()
{
     for (int i = 2; i < maxn; i++) {
    	if (!vis[i]) {
    		prime[pos++] = i;
    	}
    	for (int j = 0; j < pos && prime[j] <= maxn / i; j++) {
    		vis[i * prime[j]] = true;
    		if (i % prime[j] == 0)
    			break;
    	}
    }
    return;
}
     
int get_nums(int n, int p)
{
    int s = 0;
    while (n) {
    	s += n / p;
    	n /= p;
    }
    return s;
}
     
void multi(vector<LL> &a, int b)
{
    LL t = 0;
    for (int i = 0; i < a.size(); i++) {
    	a[i] = a[i] * b + t;
    	t = a[i] / 1000000000;
    	a[i] %= 1000000000;
    }
    while (t) {
    	a.push_back(t % 1000000000);
    	t /= 1000000000;
    }
    return;
}
     
int main()
{
    get_prime();
    int n;
    cin >> n;
    for (int i = 2; i <= 2 * n; i++)
    	if (!vis[i])
    		cnt_prime_numbers[i] = get_nums(2 * n, i) - get_nums(n, i) * 2;
    for (int i = 2, k = n + 1; i <= k; i++)
    	while (k % i == 0)
    		cnt_prime_numbers[i]--, k /= i;
    vector<LL> ans;
    ans.push_back(1);
    for (int i = 2; i <= 2 * n; i++)
    	while (cnt_prime_numbers[i]--)
    		multi(ans, i);
    reverse(ans.begin(), ans.end());
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++)
    	printf("%09lld", ans[i]);
    cout << endl;
    return 0;
}
