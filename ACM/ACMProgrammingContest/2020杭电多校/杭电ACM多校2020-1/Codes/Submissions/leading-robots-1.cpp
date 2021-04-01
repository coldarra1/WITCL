#include <bits/stdc++.h>

using namespace std;

typedef long long itype;

template <class T>
class Fraction
{
public:
	T n, d;

	Fraction(void) : n(0), d(1)
	{

	}

	Fraction(const T & n, const T & d = 1) : n(n), d(d)
	{
		refresh();
	}

	void refresh(void)
	{
		if (d < 0)
		{
			n *= -1;
			d *= -1;
		}
		T g = abs(__gcd(n, d));
		n /= g;
		d /= g;
	}

	operator long double (void) const
	{
		return (long double)n / d;
	}

	long double to_long_double(void) const
	{
		return (long double)n / d;
	}

	Fraction operator + (const Fraction & rhs) const
	{
		return Fraction(n * rhs.d + rhs.n * d, d * rhs.d);
	}

	Fraction operator - (const Fraction & rhs) const
	{
		return Fraction(n * rhs.d - rhs.n * d, d * rhs.d);
	}

	Fraction operator * (const Fraction & rhs) const
	{
		return Fraction(n * rhs.n, d * rhs.d);
	}

	Fraction operator / (const Fraction & rhs) const
	{
		return Fraction(n * rhs.d, d * rhs.n);
	}

	bool operator < (const Fraction & rhs) const
	{
		T q = n / d, rhsq = rhs.n / rhs.d;
		if (q != rhsq)
			return q < rhsq;
		else
		{
			T r = n % d, rhsr = rhs.n % rhs.d;
			return r * rhs.d < rhsr * d;
		}
	}

	bool operator == (const Fraction & rhs) const
	{
		T q = n / d, rhsq = rhs.n / rhs.d;
		if (q != rhsq)
			return false;
		else
		{
			T r = n % d, rhsr = rhs.n % rhs.d;
			return r * rhs.d == rhsr * d;
		}
	}

	bool operator <= (const Fraction & rhs) const
	{
		T q = n / d, rhsq = rhs.n / rhs.d;
		if (q != rhsq)
			return q < rhsq;
		else
		{
			T r = n % d, rhsr = rhs.n % rhs.d;
			return r * rhs.d <= rhsr * d;
		}
	}
};

class Robot
{
public:
	int p;
	int a;

	Robot(void) : p(0), a(0)
	{

	}

	Robot(const int & p, const int & a) : p(p), a(a)
	{

	}

	Fraction<itype> operator * (const Robot & rhs) const
	{
		return Fraction<itype>((long long)abs(rhs.p - p) * 2, abs(a - rhs.a));
	}

	bool operator < (const Robot & rhs) const
	{
		if (p != rhs.p)
			return p < rhs.p;
		else
			return a < rhs.a;
	}

	bool operator == (const Robot & rhs) const
	{
		return p == rhs.p && a == rhs.a;
	}
};

const int maxN = 100000;

int N;
Robot rbt[maxN];
set<Robot> mpl;
int sz;
Robot arr[maxN];
Fraction<itype> f[maxN];

int main(void)
{
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("answer.txt", "w", stdout);
#endif

	int T;
	cin >> T;
	assert(1 <= T && T <= 80);
	for (int CN = 0; CN < T; CN++)
	{
		cin >> N;
		assert(0 < N && N <= 100000);
		for (int i = 0; i < N; i++)
		{
			cin >> rbt[i].p >> rbt[i].a;
			assert(0 < rbt[i].p && rbt[i].p <= 2147483647);
			assert(0 < rbt[i].a && rbt[i].a <= 2147483647);
		}

		mpl.clear();
		sort(rbt, rbt + N);
		sz = 0;
		for (int i = 0; i < N; i++)
		{
			if (i > 0 && rbt[i - 1] == rbt[i])
				mpl.insert(rbt[i]);
			for (; sz > 0 && arr[sz - 1].a <= rbt[i].a; sz--);
			for (; sz > 1 && f[sz - 2] <= arr[sz - 1] * rbt[i]; sz--);
			arr[sz++] = rbt[i];
			if (sz >= 2)
				f[sz - 2] = arr[sz - 2] * arr[sz - 1];
		}

		int ans = 0;
		for (int i = 0; i < sz; i++)
		{
			if (!mpl.count(arr[i]))
				ans++;
		}

		cout << ans << endl;
	}

	return 0;
}
