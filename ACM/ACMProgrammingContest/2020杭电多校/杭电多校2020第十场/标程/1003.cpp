#include <cstdio>
#include <algorithm>
using namespace std;
#define W 25
#define N W + 5

int Case, s;
bool Mine[N][N];

int main()
{
    for (scanf("%d", &Case); Case; Case --)
    {
        scanf("%d", &s);
        if (s < W)
        {
            printf("%d %d\n", 1, s + 1);
            for (int i = 1; i <= s + 1; i ++)
                putchar((i & 1) ? '.' : 'X');
            puts("");
        }
        else
        {
            for (int i = 1; i <= W; i ++)
                for (int j = 1; j <= W; j ++)
                    Mine[i][j] = false;
            int a, b;
            for (a = s / 8; (s - a * 8) % 3 != 0; a --) ;
            b = (s - a * 8) / 3;
            for (int i = 1; a && i * 2 < W; i ++)
                for (int j = 1; a && j * 2 < W; j ++, a --)
                    Mine[i * 2][j * 2] = true;
            for (int i = 0; i < b; i ++)
                Mine[W][W - i] = true;
            printf("%d %d\n", W, W);
            for (int i = 1; i <= W; i ++)
            {
                for (int j = 1; j <= W; j ++)
                    putchar(Mine[i][j] ? 'X' : '.');
                puts("");
            }
        }
    }
    return 0;
}