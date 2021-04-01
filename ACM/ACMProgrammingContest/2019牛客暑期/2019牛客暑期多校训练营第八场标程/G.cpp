#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 100000 + 5

int ans, sta[N];
char s[N];

int main()
{
	scanf("%s", s);
	int n = strlen(s);
	for (int i = 0; s[i]; i ++)
	{
		sta[++ sta[0]] = s[i];
		if (sta[0] >= 3 && sta[sta[0]] == sta[sta[0] - 1] && sta[sta[0]] == sta[sta[0] - 2])
			sta[0] -= 3, ans ++;
	}
	printf("%d\n", ans);
	return 0;
}
