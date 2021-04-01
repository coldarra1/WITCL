
#include <bits/stdc++.h>
#define rep(i, n) for (int i = 1; i <= n; ++i)
using namespace std;
typedef pair<int, int> pii;
typedef long long ll;

const int maxn = 111111, maxs = (1 << 21) + 100, MOD = 998244353;

const int BUFF_SIZE = 1 << 20;
char BUFF[BUFF_SIZE], *BB, *BE;
#define gc() \
    (BB == BE ? (BE = (BB = BUFF) + fread(BUFF, 1, BUFF_SIZE, stdin), BB == BE ? EOF : *BB++) : *BB++)

template <typename T>
void read(T& x) {
    x = 0;
    int f = 1;
    char ch = gc();
    while (!isdigit(ch)) {
        if (ch == '-')
            f = -1;
        ch = gc();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = gc();
    }
    x *= f;
}
template <typename T, typename... Args>
void read(T& x, Args&... args) {
    read(x), read(args...);
}
template <typename T>
void write(T x) {
    if (x < 0)
        putchar('-'), write(-x);
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

int mo(int x) {
    if (x >= MOD)
        x -= MOD;
    if (x < 0)
        x += MOD;
    return x;
}
int muln(int x, int y) { return 1LL * x * y % MOD; }
int Len = 1 << 21, Base = 21;

inline void fmt_or(vector<int>& A, int dmt = 1, int base = Base) {
    int len = 1 << base;
    for (int i = 1; i < len; i <<= 1)
        for (int j = 0, t = i << 1; j < len; j += t)
            for (int k = j, K = j + i; k < K; ++k) A[k + i] = mo(A[k + i] + dmt * A[k]);
}

vector<int> pc;
void get_top(int sz) {
    pc.resize(sz, 0);
    for (int i = 1; i < sz; ++i) pc[i] = pc[i >> 1] + (i & 1);
}

vector<int> subset_conv(vector<int> A, vector<int> B, int base) {
    int len = 1 << base;
    vector<int> H(len);
    vector<vector<int> > siga(base + 1, vector<int>(len, 0)), sigb = siga, sigh = siga;
    for (int S = 0; S < len; ++S) siga[pc[S]][S] = A[S], sigb[pc[S]][S] = B[S];
    for (int i = 0; i <= base; ++i) {
        fmt_or(siga[i], 1, base);
        fmt_or(sigb[i], 1, base);
        for (int S = 0; S < len; ++S)
            for (int j = 0; j <= i; ++j) sigh[i][S] = mo(sigh[i][S] + muln(siga[j][S], sigb[i - j][S]));
        fmt_or(sigh[i], -1, base);
    }
    for (int S = 0; S < len; ++S) H[S] = sigh[pc[S]][S];
    return H;
}
vector<int> conv(const vector<int>& p) {
    // A[n][S] = \sum_{ T \in S-\{n\} } A[pc(T)][T] \cdot p[n][S-T]
    get_top(Len);
    vector<int> ret(Len, 0);
    ret[0] = 1;
    for (int n = 0; n < Base; ++n) {
        int ful = 1 << n;
        auto A = vector<int>(ret.begin(), ret.begin() + ful);
        auto B = vector<int>(p.begin() + ful, p.begin() + ful * 2);
        A = subset_conv(A, B, n);
        for (int i = ful; i < ful * 2; ++i) ret[i] = A[i - ful];
    }
    return ret;
}

int main() {
    int n, q, prob, b;
    vector<int> p(Len, 0);
    read(n);
    rep(i, n) {
        read(prob, b);
        p[b] = mo(p[b] + prob);
    }
    auto ans = conv(p);
    read(q);
    while (q--) {
        read(b);
        write(ans[b]);
        putchar('\n');
    }

    return 0;
}
