#include <bits/stdc++.h>

using namespace std;

int random() {
	return (rand() << 15) | rand();
}

int random(int n) {
	return random() % n;
}

int random(const int &l, const int &r) {
	return l + random(r - l);
}

long long randomll() {
	return ((long long)random() << 30) | random();
}

long long randomll(const long long &n) {
	return randomll() % n;
}

long long randomll(const long long &l, const long long &r) {
	return l + randomll(r - l);
}

long double randoml() {
	return (long double)randomll() / (1ll << 60);
}

long double randoml(const long double &n) {
	return randoml() * n;
}

long double randoml(const long double &l, const long double &r) {
	return l + randoml(r - l);
}

const long double pi = acosl(-1); // 3.1415926535897932384626433832795
const long double radian = 180 / pi; // 57.295779513082320876798154814105
const long double eps = 1e-12;
const int inf = 0x7f7f7f7f;
const long long infll = 0x7f7f7f7f7f7f7f7fll;
const long double infl = 1e20;

inline int sgn(const long double &x) {
	return (x > eps) - (x < -eps);
}

inline int sgn(const long long &x) {
	return (x > 0) - (x < 0);
}

inline long double sqr(const long double &x) {
	return x * x;
}

inline long long sqr(const long long &x) {
	return x * x;
}

inline long double refresh(const long double &x) {
	if (x < -1 + eps)
		return -1;
	else if (x > 1 - eps)
		return 1;
	else
		return x;
}

struct Point {
	long long x, y;

	Point() : x(0), y(0) {

	}

	Point(const long long &x, const long long &y) : x(x), y(y) {

	}

	Point(const Point &src) : x(src.x), y(src.y) {

	}

	long double length() const {
		return sqrtl(sqr(x) + sqr(y));
	}

	long long length2() const {
		return sqr(x) + sqr(y);
	}

	long double distance(const Point &rhs) const {
		return (rhs - *this).length();
	}

	long long distance2(const Point &rhs) const {
		return (rhs - *this).length2();
	}

	Point conjugate() const {
		return Point(x, -y);
	}

	Point normal(const bool &lft = true) const {
		return lft ? Point(-y, x) : Point(y, -x);
	}

	Point moderate() const {
		return *this * (y < 0 || y == 0 && x < 0 ? -1 : 1);
	}

	long long vect(const Point &lhs, const Point &rhs) const {
		return (lhs - *this) * (rhs - *this);
	}

	long long scal(const Point &lhs, const Point &rhs) const {
		return (lhs - *this) & (rhs - *this);
	}

	long double distance_to_line(const Point &p, const Point &q) const {
		return fabsl(p.vect(q, *this) / p.distance(q));
	}

	long double distance_to_segment(const Point &p, const Point &q) const {
		if (p.scal(q, *this) < 0)
			return p.distance(*this);
		else if (q.scal(p, *this) < 0)
			return q.distance(*this);
		else
			return this->distance_to_line(p, q);
	}

	bool on_line(const Point &p, const Point &q) const {
		return sgn(this->vect(p, q)) == 0;
	}

	bool on_halfline(const Point &p, const Point &q, const bool &inclusive = true) const {
		if (*this == p)
			return inclusive;
		else
			return this->on_line(p, q) && sgn(p.scal(q, *this)) >= 0;
	}

	bool on_segment(const Point &p, const Point &q, const bool &inclusive = true) const {
		if (*this == p || *this == q)
			return inclusive;
		else
			return this->on_line(p, q) && sgn(this->scal(p, q)) <= 0;
	}

	bool in_triangle(const Point &u, const Point &v, const Point &w, const bool &inclusive = true) const {
		Point p[3] = {u, v, w};
		if (sgn(u.vect(v, w)) < 0)
			reverse(p, p + 3);
		for (int i = 0; i < 3; i++) {
			if (this->on_segment(p[i], p[(i + 1) % 3]))
				return inclusive;
			else if (sgn(this->vect(p[i], p[(i + 1) % 3])) < 0)
				return false;
		}
		return true;
	}

	bool in_angle(const Point &o, const Point &p, const Point &q, const bool &inclusive = true) const {
		if (this->on_halfline(o, p) || this->on_halfline(o, q))
			return inclusive;
		int vp = sgn(o.vect(p, *this)), vq = sgn(o.vect(*this, q));
		if (sgn(o.vect(p, q)) >= 0)
			return vp > 0 && vq > 0;
		else
			return vp > 0 || vq > 0;
	}

	Point operator + (const Point &rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}

	Point operator - (const Point &rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}

	Point operator * (const long long &rhs) const {
		return Point(x * rhs, y * rhs);
	}

	Point operator / (const long long &rhs) const {
		return Point(x / rhs, y / rhs);
	}

	long long operator * (const Point &rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	long long operator & (const Point &rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	Point operator << (const Point &rhs) const {
		return Point(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
	}

	long double operator ^ (const Point &rhs) const {
		int s = sgn(*this * rhs);
		long double a = acosl(refresh((long double)(*this & rhs) / this->length() / rhs.length()));
		return s < 0 ? -a : a;
	}

	bool operator == (const Point &rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	inline int quadrant() const {
		if (x == 0 && y == 0)
			return 0;
		else if (x < 0 && y < 0)
			return 1;
		else if (x == 0 && y < 0)
			return 2;
		else if (x > 0 && y < 0)
			return 3;
		else if (x > 0 && y == 0)
			return 4;
		else if (x > 0 && y > 0)
			return 5;
		else if (x == 0 && y > 0)
			return 6;
		else if (x < 0 && y > 0)
			return 7;
		else
			return 8;
	}
 
	bool operator < (const Point &rhs) const {
		int lq = quadrant(), rq = rhs.quadrant();
		if (lq != rq)
			return lq < rq;
		else {
			int s = sgn(*this * rhs);
			return s != 0 ? s > 0 : sgn(length2() - rhs.length2()) < 0;
		}
	}

	bool on_left(const Point &rhs, const bool &inclusive = true) const {
		long long s = *this * rhs, t = *this & rhs;
		return s == 0 ? t >= 0 || inclusive : s > 0;
	}

	bool on_right(const Point &rhs, const bool &inclusive = true) const {
		long long s = *this * rhs, t = *this & rhs;
		return s == 0 ? t >= 0 || inclusive : s < 0;
	}
};

inline bool xycmp(const Point &lhs, const Point &rhs) {
	if (lhs.x != rhs.x)
		return lhs.x < rhs.x;
	else
		return lhs.y < rhs.y;
}

inline bool yxcmp(const Point &lhs, const Point &rhs) {
	if (lhs.y != rhs.y)
		return lhs.y < rhs.y;
	else
		return lhs.x < rhs.x;
}

void convex_hull(Point *first, Point *last, vector<Point> &ans) {
	Point *&p = first;
	const int n = last - first;
	int mn = -1;
	for(int i = 0; i < n; i++) {
		if(mn == -1 || yxcmp(p[i], p[mn]))
			mn = i;
	}
	Point org = p[mn];
	for(int i = 0; i < n; ++i)
		p[i] = p[i] - org;
	sort(p, p + n);
	for (int i = 0; i < n; i++)
		p[i] = org + p[i];

	ans.resize(n);
	int sz = 0;
	ans[sz++] = p[0];
	for(int i = 1; i < n; i++) {
		for(; sz > 1 && sgn(ans[sz - 2].vect(ans[sz - 1], p[i])) <= 0; sz--);
		ans[sz++] = p[i];
	}
	ans.resize(sz);
}

Point random_point(const int &rm, const int &rM) {
	long double a = randoml(0, pi * 2);
	long double r = randoml(rm, rM);
	return Point(r * cosl(a), r * sinl(a));
}

const int maxn = 1000;
const int maxp = 10000;

Point p[maxp];

int main() {
	ios::sync_with_stdio(false);
	
	srand(time(NULL));

	freopen("data.in", "w", stdout);

	cout << 100 << endl;
	
	cout << 4 << " " << 1 << endl;
	cout << 1 << " " << 0 << endl;
	cout << 0 << " " << 0 << endl;
	cout << 4 << " " << 0 << endl;
	cout << 4 << " " << 4 << endl;
	cout << 0 << " " << 4 << endl;

	cout << 4 << " " << 3 << endl;
	cout << 1 << " " << 0 << endl;
	cout << 0 << " " << 0 << endl;
	cout << 4 << " " << 0 << endl;
	cout << 4 << " " << 4 << endl;
	cout << 0 << " " << 4 << endl;

	int nmax = 4, rmax = 1;
	for (int T = 3; T <= 100; T++) {
		for (int i = 0; i < maxp; i++)
			p[i] = random_point(9000, 10000);
		vector<Point> hull;
		convex_hull(p, p + maxp, hull);
		if (hull.size() > maxn)
			hull.resize(maxn);
		if (random(3) == 0)
			reverse(hull.begin(), hull.end());
		int r = random(9250, 10001);

		nmax = max(nmax, (int)hull.size());
		rmax = max(rmax, r);
		cout << hull.size() << ' ' << r << endl;
		cout << random(1001) << ' ' << random(1001) << endl;
		for (const auto &t : hull)
			cout << t.x << ' ' << t.y << endl;
	}
	
	cerr << "maxn = " << nmax << ", maxr = " << rmax << endl;

	return 0;
}
