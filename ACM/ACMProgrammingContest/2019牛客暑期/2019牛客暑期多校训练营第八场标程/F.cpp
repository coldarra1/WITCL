#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
#define N 1000 + 5
#define M 2048 + 5
#define mp make_pair
#define ls(x) x << 1
#define rs(x) x << 1 | 1

int n, X[N], Y[N], D[N], Ord[N], Last[N], Del[M], Sum[M];
LL ans;

inline LL Cross(int x_1, int y_1, int x_2, int y_2)
{
	return 1LL * x_1 * y_2 - 1LL * x_2 * y_1;
}

inline LL Cross(int st, int t_1, int t_2)
{
	int x_1 = X[t_1] - X[st], y_1 = Y[t_1] - Y[st];
	int x_2 = X[t_2] - X[st], y_2 = Y[t_2] - Y[st];
	return Cross(x_1, y_1, x_2, y_2);
}

inline LL Dot(int x_1, int y_1, int x_2, int y_2)
{
	return 1LL * x_1 * x_2 + 1LL * y_1 * y_2;
}

inline LL Dot(int st, int t_1, int t_2)
{
	int x_1 = X[t_1] - X[st], y_1 = Y[t_1] - Y[st];
	int x_2 = X[t_2] - X[st], y_2 = Y[t_2] - Y[st];
	return Dot(x_1, y_1, x_2, y_2);
}

inline LL Dis2(int u, int v)
{
	int _x = X[u] - X[v], _y = Y[u] - Y[v];
	return 1LL * _x * _x + 1LL * _y * _y;
}

inline int Pre(int x)
{
	return x == 1 ? n - 1 : x - 1;
}

inline int Nxt(int x)
{
	return x == n - 1 ? 1 : x + 1;
}

inline void apply(int x, int l, int r, int k)
{
	Del[x] += k, Sum[x] += (r - l + 1) * k;
}

inline void push(int x, int l, int r)
{
	if (Del[x])
	{
		int mid = l + r >> 1;
		apply(ls(x), l, mid, Del[x]);
		apply(rs(x), mid + 1, r, Del[x]);
		Del[x] = 0;
	}
}

inline void update(int x)
{
	Sum[x] = Sum[ls(x)] + Sum[rs(x)];
}

void Build(int x, int l, int r)
{
    Del[x] = Sum[x] = 0;
    if (l == r)
    {
        Sum[x] = D[l];
        return ;
    }
    int mid = l + r >> 1;
    Build(ls(x), l, mid);
    Build(rs(x), mid + 1, r);
    update(x);
}

void Modify(int x, int l, int r, int s, int t, int k, int op = 0)
{
	if (l == s && r == t)
	{
        if (!op)
			apply(x, l, r, k);
        else Del[x] = Sum[x] = 0;
		return ;
	}
	push(x, l, r);
	int mid = l + r >> 1;
	if (t <= mid)
		Modify(ls(x), l, mid, s, t, k, op);
	else if (s > mid)
		Modify(rs(x), mid + 1, r, s, t, k, op);
	else Modify(ls(x), l, mid, s, mid, k, op), Modify(rs(x), mid + 1, r, mid + 1, t, k, op);
	update(x);
}

inline int Range(int pre, int nxt)
{
	if (pre <= nxt)
		return nxt - pre;
	else return nxt + n - 1 - pre;
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i ++)
		scanf("%d%d", X + i, Y + i);
	for (int a = 1; a <= n; a ++)
	{
		for (int i = 1; i < n; i ++)
			Ord[i] = i + (i >= a);
		sort(Ord + 1, Ord + n, [a](int u, int v){
			int f_u = mp(Y[u], X[u]) > mp(Y[a], X[a]);
			int f_v = mp(Y[v], X[v]) > mp(Y[a], X[a]);
			if (f_u != f_v)
				return f_u > f_v;
			return Cross(a, u, v) > 0 || (Cross(a, u, v) == 0 && Dis2(a, u) < Dis2(a, v));
		});
		Last[1] = n - 1;
		for (int i = 2; i < n; i ++)
		{
			if (Cross(a, Ord[i - 1], Ord[i]) == 0 && Dot(a, Ord[i - 1], Ord[i]) > 0)
				Last[i] = Last[i - 1];
			else Last[i] = i - 1;
		}
		int b = 1, d_l, d_r, c_l, c_r;
		for (d_l = Nxt(b); d_l != b && Cross(a, Ord[b], Ord[d_l]) == 0 && Dot(a, Ord[b], Ord[d_l]) > 0; d_l = Nxt(d_l)) ;
		for (d_r = d_l; d_r != b && (Cross(a, Ord[b], Ord[d_r]) > 0 || (Cross(a, Ord[b], Ord[d_r]) == 0 && Dot(a, Ord[b], Ord[d_r]) > 0)); d_r = Nxt(d_r)) ;
		for (c_l = d_r; c_l != b && (Cross(a, Ord[b], Ord[c_l]) > 0 || (Cross(a, Ord[b], Ord[c_l]) == 0 && Dot(a, Ord[b], Ord[c_l]) < 0)); c_l = Nxt(c_l)) ;
		for (c_r = c_l; c_r != b && Cross(a, Ord[b], Ord[c_r]) < 0; c_r = Nxt(c_r)) ;
		for (int i = 1; i < n; i ++)
            D[i] = 0;
        for (int c = c_l, d = d_l; c != c_r; c = Nxt(c))
		{
			for (; d != d_r && Cross(a, Ord[c], Ord[d]) >= 0; d = Nxt(d)) ;
            D[c] = Range(d, d_r);
		}
        Build(1, 1, n - 1);
		while (b = Nxt(b), ans += Sum[1], b != 1)
		{
			for (; c_l != b && (Cross(a, Ord[b], Ord[c_l]) > 0 || (Cross(a, Ord[b], Ord[c_l]) == 0 && Dot(a, Ord[b], Ord[c_l]) < 0)); c_l = Nxt(c_l))
				Modify(1, 1, n - 1, c_l, c_l, 0, 1);
			for (; c_r != b && Cross(a, Ord[b], Ord[c_r]) < 0; c_r = Nxt(c_r)) ;
			for (; d_r != b && (Cross(a, Ord[b], Ord[d_r]) > 0 || (Cross(a, Ord[b], Ord[d_r]) == 0 && Dot(a, Ord[b], Ord[d_r]) > 0)); d_r = Nxt(d_r))
				if (Cross(a, Ord[d_r], Ord[c_l]) > 0)
				{
					int boundry = Pre(c_r);
					if (Cross(a, Ord[d_r], Ord[boundry]) <= 0)
						boundry = Last[boundry];
					if (boundry >= c_l)
						Modify(1, 1, n - 1, c_l, boundry, 1);
					else {
                        Del[1] ++, Sum[1] += n - 1;
                        if (boundry + 1 <= c_l - 1)
                        	Modify(1, 1, n - 1, boundry + 1, c_l - 1, -1);
                    }
				}
		}
	}
	printf("%lld\n", ans / 3);
	return 0;
}

