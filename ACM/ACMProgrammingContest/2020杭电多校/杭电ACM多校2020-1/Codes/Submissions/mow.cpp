#include <bits/stdc++.h>

using namespace std;

using ftype = long double;

const ftype pi = acosl(-1); // 3.1415926535897932384626433832795l
const ftype eps = 1e-12l;

template<typename T>
inline int sgn(const T &x) {
	return (x > eps) - (x < -eps);
}

#define Vector Point

template<typename T>
struct Point {
	T x, y;
	Point(const T &x = T(), const T &y = T()) : x(x), y(y) {}
	template<typename S>
	Point(const Point<S> &src) : x(src.x), y(src.y) {}
	Vector operator + (const Vector &rhs) const {
		return Vector(x + rhs.x, y + rhs.y);
	}
	Vector operator - (const Vector &rhs) const {
		return Vector(x - rhs.x, y - rhs.y);
	}
	T length() const {
		return sqrtl(x * x + y * y);
	}
	T distance(const Point &rhs) const {
		return (rhs - *this).length();
	}
	Vector operator * (const T &rhs) const {
		return Vector(x * rhs, y * rhs);
	}
	Vector operator / (const T &rhs) const {
		return Vector(x / rhs, y / rhs);
	}
	T operator * (const Vector &rhs) const {
		return x * rhs.y - y * rhs.x;
	}
	T operator & (const Vector &rhs) const {
		return x * rhs.x + y * rhs.y;
	}
	T cross(const Point &lhs, const Point &rhs) const {
		return (lhs - *this) * (rhs - *this);
	}
	int quadrant() const {
		int xs = sgn(x), ys = sgn(y);
		return xs == 0 && ys == 0 ? -1 : ((ys < 0 || ys == 0 && xs > 0) ? 0 : 1);
	}
	bool operator < (const Vector &rhs) const {
		int lq = quadrant(), rq = rhs.quadrant();
		if (lq != rq) return lq < rq;
		int s = sgn(*this * rhs);
		return s ? s > 0 : sgn(length() - rhs.length()) < 0;
	}
	Vector unit(const T &n = 1) const {
		T l = length();
		return sgn(l) == 0 ? Vector(n, 0) : Vector(x * n / l, y * n / l);
	}
	Vector normal(const bool &rht = false) const {
		return rht ? Vector(y, -x) : Vector(-y, x);
	}
};

template<typename T>
T polygon_area(const vector<Point<T>> &p) {
	const int n = p.size();
	T ans = 0;
	for (int i = 0; i < n; i++) ans += p[i] * p[(i + 1) % n];
	return ans / 2;
}

template<typename T>
Point<T> line_line_intersection(const Point<T> & p1, const Point<T> & p2, const Point<T> & q1, const Point<T> & q2) {
	T pv1 = p1.cross(p2, q1), pv2 = p1.cross(p2, q2);
	return q1 * (-pv2 / (pv1 - pv2)) + q2 * (pv1 / (pv1 - pv2));
}

template<typename T>
struct Line {
	Point<T> u, v;
	Line(const Point<T> &u = Point<T>(), const Point<T> &v = Point<T>()) : u(u), v(v) {}
	Line(const T &px, const T &py, const T &qx, const T &qy) : u(px, py), v(qx, qy) {}
	T operator * (const Line &rhs) const {
		return (v - u) * (rhs.v - rhs.u);
	}
	T operator & (const Line &rhs) const {
		return (v - u) & (rhs.v - rhs.u);
	}
	bool operator < (const Line &rhs) const {
		int vs = sgn((v - u) * (rhs.v - rhs.u)), ss = sgn((v - u) & (rhs.v - rhs.u));
		return vs == 0 && ss > 0 ? on_left(rhs.u, false) : v - u < rhs.v - rhs.u;
	}
	bool on_left(const Point<T> &p, const bool &inclusive = true) const {
		return p.cross(u, v) > 0;
	}
	bool on_right(const Point<T> &p, const bool &inclusive = true) const {
		return p.cross(u, v) < 0;
	}
};

template<typename T>
Point<T> line_line_intersection(const Line<T> &lhs, const Line<T> &rhs) {
	return line_line_intersection(lhs.u, lhs.v, rhs.u, rhs.v);
}

template<typename T>
bool half_plane_intersection(vector<Line<T>> &L, vector<Point<T>> &ans) {
	const int n = L.size();
	sort(L.begin(), L.end());
	int first = 0, last = 0;
	vector<Point<T>> p(n);
	vector<Line<T>> q(n);
	q[last++] = L[0];
	for (int i = 1; i < n; i++) {
		for (; first + 1 < last && L[i].on_right(p[last - 2]); last--);
		for (; first + 1 < last && L[i].on_right(p[first]); first++);
		q[last++] = L[i];
		if (sgn(q[last - 2] * q[last - 1]) == 0) {
			last--;
			if (q[last - 1].on_left(L[i].u)) q[last - 1] = L[i];
		}
		if (first + 1 < last) p[last - 2] = line_line_intersection(q[last - 2], q[last - 1]);
	}
	for (; first + 1 < last && q[first].on_right(p[last - 2]); last--);
	if (last - first <= 2) return false;
	p[last - 1] = line_line_intersection(q[first], q[last - 1]);
	ans = vector<Point<T>>(p.begin() + first, p.begin() + last);
	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int ncase;
	for (cin >> ncase; ncase--; ) {
		int n, r, A, B; cin >> n >> r >> A >> B;
		vector<Point<ftype>> p(n);
		for (auto &t : p) cin >> t.x >> t.y;
		ftype s = polygon_area(p);
		if (sgn(s) < 0) {
			reverse(p.begin(), p.end());
			s *= -1;
		}
		ftype ans = s * A;
		vector<Line<ftype>> L;
		vector<Point<ftype>> q;
		for (int i = 0; i < n; i++) {
			Point<ftype> nml = (p[(i + 1) % n] - p[i]).normal().unit(r);
			L.emplace_back(p[i] + nml, p[(i + 1) % n] + nml);
		}
		if (half_plane_intersection(L, q)) {
			const int m = q.size();
			ftype l = 0;
			for (int i = 0; i < m; i++) l += q[i].distance(q[(i + 1) % m]);
			ftype a = polygon_area(q) + l * r + r * r * pi;
			ans = min(ans, a * B + (s - a) * A);
		}
		cout << fixed << setprecision(20) << ans << endl;
	}
	return 0;
}
