#include <cstdio>
#include <algorithm>
using namespace std;
#define N 3000 + 5

int n, m, ans, Map[N][N], Sum[N][N], Up[N][N], Stack[N], Height[N];
char s[N];

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i ++)
	{
		scanf("%s", s + 1);
		for (int j = 1; j <= m + 1; j ++)
		{
			Map[i][j] = j <= m ? (s[j] == '1') : 0;
			Sum[i][j] = Sum[i][j - 1] + Map[i][j];
			Up[i][j] = Map[i][j] ? Up[i - 1][j] + 1 : 0;
		}
	}
	for (int i = 1; i <= n; i ++)
		for (int j = 1, sz = 0; j <= m + 1; j ++)
		{
			int last = j;
			for (; sz && Height[sz] > Up[i][j]; sz --)
			{
				if (i == n || (Sum[i + 1][j - 1] - Sum[i + 1][Stack[sz] - 1]) < j - Stack[sz]) ans ++;
				last = Stack[sz];
			}
			if (Up[i][j] && (!sz || Height[sz] < Up[i][j]))
				Stack[++ sz] = last, Height[sz] = Up[i][j];
		}
	printf("%d\n", ans);
	return 0;
}
