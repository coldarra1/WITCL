#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;
typedef unsigned long long uLL;
#define N 100000 + 5
#define L 1000000 + 5
#define Base 233
#define K 5
#define Mod 998244353

int n, ans, Cnt[L];
uLL Pow[L];
vector<int> Next[N];
vector<uLL> Hash[N];
char s[L];
unordered_map<uLL, int> Map;

void Handle(int id)
{
	int len = strlen(s);
	Next[id].resize(len + 1);
	Hash[id].resize(len + 1);
	Next[id][0] = -1;
	for (int k = -1, j = 0; j < len; Next[id][++ j] = ++ k)
		for (; ~k && s[k] != s[j]; k = Next[id][k]) ;
	for (int i = 1; i <= len; i ++)
		Hash[id][i] = Hash[id][i - 1] * Base + s[i - 1] - 'a' + K;
	for (int l = 0; l < len; l ++)
	{
		uLL val = Hash[id][len] - Hash[id][l] * Pow[len - l];
		Map[val] ++;
	}
}

int main()
{
	Pow[0] = 1;
	for (int i = 1; i < L; i ++)
		Pow[i] = Pow[i - 1] * Base;
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
	{
		scanf("%s", s);
		Handle(i);
	}
	for (int i = 1; i <= n; i ++)
	{
		int len = int(Hash[i].size()) - 1;
		for (int j = 1; j <= len; j ++)
		{
			Cnt[j] = Map[Hash[i][j]];
			Cnt[Next[i][j]] -= Cnt[j];
		}
		for (int j = 1; j <= len; j ++)
			ans = (1LL * Cnt[j] * j % Mod * j + ans) % Mod;
	}
	printf("%d\n", ans);
	return 0;
}
