#include <cstdio>
#include <algorithm>
#include <numeric>

static const int MAXN = 505;

static int n;
static int p[MAXN * 2], q[MAXN];

static inline int inc_subseq(int n, int *a)
{
    static int f[MAXN];
    std::fill(f, f + MAXN, 0);

    for (int i = 0; i < n; ++i) {
        int last = 0;
        for (int j = 0; j < a[i]; ++j)
            last = std::max(last, f[j]);
        f[a[i]] = std::max(f[a[i]], last + 1);
    }

    return *std::max_element(f, f + MAXN);
}

int main()
{
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", &p[i]);
        p[i] = p[i + n] = p[i] - 1;
        q[p[i]] = i;
    }

    int ans = n - 1;

    for (int i = 0; i < n; ++i)
        ans = std::min(ans, n - inc_subseq(n, p + q[i]));

    printf("%d\n", ans);

    return 0;
}
