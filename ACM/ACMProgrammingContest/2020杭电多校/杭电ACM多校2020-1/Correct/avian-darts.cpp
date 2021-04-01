#include <bits/stdc++.h>
using namespace std;

using ftype = long double;

const ftype pi = acosl(-1); // 3.1415926535897932384626433832795l
const ftype radian = 180 / pi; // 57.295779513082320876798154814105l
const ftype eps = 1e-12l;

template <typename T>
inline int sgn(const T &x) {
	return (x > eps) - (x < -eps);
}

#define Vector Point

template <typename T>
struct Point {
	T x, y, z;
	Point(const T &x = T(), const T &y = T(), const T &z = T()) : x(x), y(y), z(z) {}
	Vector operator+(const Vector &rhs) const {
		return {x + rhs.x, y + rhs.y, z + rhs.z};
	}
	Vector operator-(const Vector &rhs) const {
		return {x - rhs.x, y - rhs.y, z - rhs.z};
	}
	Vector operator*(const T &rhs) const {
		return {x * rhs, y * rhs, z * rhs};
	}
	Vector operator/(const T &rhs) const {
		return {x / rhs, y / rhs, z / rhs};
	}
	Vector operator*(const Vector &rhs) const {
		return {y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x};
	}
	T operator&(const Vector &rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}
	T dot(const Point &lhs, const Point &rhs) const {
		return (lhs - *this) & (rhs - *this);
	}
	T length2() const {
		return *this & *this;
	}
	bool operator==(const Point &rhs) const {
		return sgn(x - rhs.x) == 0 && sgn(y - rhs.y) == 0 && sgn(z - rhs.z) == 0;
	}
	Vector unit(const T &n = 1) const {
		T l = sqrtl(length2());
		return sgn(l) == 0 ? Vector(n, 0, 0) : Vector(x * n / l, y * n / l, z * n / l);
	}
	Point rotate(const Point &p, const Point &q, const T &a) const {
		if (p == q) return *this;
		Point t = project(p, q), x = *this - t, y = (q - p).unit() * x;
		return t + x * cosl(a) + y * sinl(a);
	}
	Point project(const Point &p, const Point &q) const {
		return p == q ? p : p + (q - p) * p.dot(q, *this) / (q - p).length2();
	}
};

const Point<ftype> O(0, 0, 0);

Point<ftype> P;
Vector<ftype> X, Y, Z;

void aerobatic(const ftype &wx, const ftype &wy, const ftype &wz, const ftype &v, const ftype &t) {
	Vector<ftype> WX = X * wx, WY = Y * wy, WZ = Z * wz, W = WX + WY + WZ, V = X * v;
	ftype w = sqrtl(W.length2());
	if (sgn(w) == 0) P = P + V * t;
	else {
		Vector<ftype> Vp = V.project(O, W), Vt = V - Vp;
		Vector<ftype> S = P - Vt * W / W.length2();
		P = P.rotate(S, S + W, w * t) + Vp * t;
		X = X.rotate(O, W, w * t);
		Y = Y.rotate(O, W, w * t);
		Z = Z.rotate(O, W, w * t);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cout << fixed << setprecision(15);
	for (int n; cin >> n; ) {
		P = O;
		X = Vector<ftype>(1, 0, 0);
		Y = Vector<ftype>(0, 1, 0);
		Z = Vector<ftype>(0, 0, 1);
		for (int i = 0; i < n; i++) {
			int wx, wy, wz, v, t; cin >> wx >> wy >> wz >> v >> t;
			aerobatic(wx / radian, wy / radian, wz / radian, v, t);
		}
		cout << P.x << " " << P.y << " " << P.z << '\n';
		cout << X.x << " " << X.y << " " << X.z << '\n';
		cout << Y.x << " " << Y.y << " " << Y.z << '\n';
		cout << Z.x << " " << Z.y << " " << Z.z << "\n\n";
	}
	return 0;
}
