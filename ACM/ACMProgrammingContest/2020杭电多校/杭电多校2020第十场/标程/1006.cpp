#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
#define N 50000 + 5
#define W 900000000
#define mp make_pair

#define ACCURATE

#ifdef ACCURATE
using real = long double;
#define Acos acosl
#define Cos cosl
#define Sin sinl
#define Round lroundl
#else
using real = double;
#define Acos acos
#define Cos cos
#define Sin sin
#define Round lround
#endif

const real eps = 1e-9;
const real pi = Acos(-1.0);

int Case, n, X[N], Y[N], Ord[N], _Ord[N], Ax[4], Ay[4];
bool Flag[N];
real Val[N];

int Calc(real angle)
{
    real sin_a = Sin(angle), cos_a = Cos(angle);
    for (int i = 1; i <= n; i ++)
    {
        _Ord[i] = i;
        Val[i] = cos_a * Y[i] - sin_a * X[i];
    }
    sort(_Ord + 1, _Ord + n + 1, [](int u, int v) {
        return Val[u] > Val[v];
    });
    int ret = 0;
    for (int i = 1; i * 2 <= n; i ++)
        ret += Flag[_Ord[i]];
    return ret;
}

int main()
{
    for (scanf("%d", &Case); Case; Case --)
    {
        scanf("%d", &n);
        for (int i = 1; i <= n; i ++)
        {
            scanf("%d%d", X + i, Y + i);
            Ord[i] = i, Flag[i] = false;
        }
        sort(Ord + 1, Ord + n + 1, [](int u, int v) {
            return mp(Y[u], X[u]) < mp(Y[v], X[v]);
        });
        for (int i = 1; i * 2 <= n; i ++)
            Flag[Ord[i]] = true;
            
        Ax[0] = -W, Ax[1] = W + X[Ord[n / 2]] + X[Ord[n / 2] + 1];
        if (Y[Ord[n / 2]] == Y[Ord[n / 2 + 1]])
            Ay[0] = Y[Ord[n / 2 + 1]] + 1, Ay[1] = Y[Ord[n / 2]] - 1;
        else Ay[0] = Y[Ord[n / 2 + 1]], Ay[1] = Y[Ord[n / 2]];
        
        real l = 0.0, r = pi;
        while (r - l > eps)
        {
            real mid = (l + r) / 2;
            int cnt = Calc(mid);
            if (cnt >= n / 4)
                r = mid;
            else l = mid;
        }
        Calc(r);
        
        int dx = X[_Ord[n / 2 + 1]] - X[_Ord[n / 2]];
        int dy = Y[_Ord[n / 2 + 1]] - Y[_Ord[n / 2]];
        int d = max(abs(dx), abs(dy)), times = W / d;
        dx *= times, dy *= times;
        Ax[2] = X[_Ord[n / 2]] - dx + 1, Ay[2] = Y[_Ord[n / 2]] - dy;
        Ax[3] = X[_Ord[n / 2 + 1]] + dx - 1, Ay[3] = Y[_Ord[n / 2 + 1]] + dy;
        
        for (int i = 0; i < 4; i ++)
            printf("%d %d%c", Ax[i], Ay[i], (i & 1) ? '\n' : ' ');
    }
    return 0;
}