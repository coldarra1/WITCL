#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <ctime>
#include <iostream>
#include <queue>
#define FILL(a, n, x) memset((a), (x), sizeof ((a)[0]) * (n))
#define FILLA(a, x) memset((a), (x), sizeof (a))
#define COPY(a, n, b) memcpy((b), (a), sizeof ((a)[0]) * (n))
#define COPYA(a, b) memcpy((b), (a), sizeof (a))
using namespace std;

typedef pair<int, int> pii;
typedef long long li;
typedef unsigned long long lu;
typedef double real;

const int inf = ~0U >> 2;
const li infl = ~0LLU >> 2;

template <class T> inline void Min(T &x, T y) { if (y < x) x = y; }
template <class T> inline void Max(T &x, T y) { if (y > x) x = y; }

const real pi = acos(-1.0);
const real eps = 1e-15;
const real eps_sqr = eps * eps;

inline real sqr(real x) {
  return x * x;
}

inline int fcmp(real x, real y) {
  return fabs(x - y) <= eps ? 0 : x < y ? -1 : 1;
}

inline bool IsZero(real x) {
  return fcmp(x, 0) == 0;
}

inline real Acos(real x) {
  if (x <= -1) x = -1;
  if (x >= 1) x = 1;
  return acos(x);
}

inline real Asin(real x) {
  if (x <= -1) x = -1;
  if (x >= 1) x = 1;
  return asin(x);
}

inline real Sqrt(real x) {
  if (x <= 0) x = 0;
  return sqrt(x);
}

inline void ReadReal(real &x) {
  cin >> x;
}

inline void WriteReal(real x) {
  double y = x;
  printf("%.20lf", y);
}

inline real RandomReal(void) {
  return rand() / (real)RAND_MAX;
}

// ----------------------------------------

#define DEF_OP(T, R, S1, S2)                    \
  T operator S2 (R __t) const {                 \
    T __a = *this;                              \
    __a S1 __t;                                 \
    return __a;                                 \
  }

struct Interval {
  real l, r;
};

struct Vec2 {
  real x, y;

  void operator += (const Vec2 &b) {
    x += b.x;
    y += b.y;
  }

  void operator -= (const Vec2 &b) {
    x -= b.x;
    y -= b.y;
  }

  void operator *= (real c) {
    x *= c;
    y *= c;
  }

  void operator /= (real c) {
    x /= c;
    y /= c;
  }

  friend Vec2 operator * (real c, const Vec2 &a) {
    return {a.x * c, a.y * c};
  }

  Vec2 operator + (void) const {
    return *this;
  }

  Vec2 operator - (void) const {
    return {-x, -y};
  }

  DEF_OP(Vec2, const Vec2 &, +=, +)
  DEF_OP(Vec2, const Vec2 &, -=, -)
  DEF_OP(Vec2, real, *=, *)
  DEF_OP(Vec2, real, /=, /)

  // ----------------------------------------

  real dot(const Vec2 &b) const {
    return x * b.x + y * b.y;
  }

  real det(const Vec2 &b) const {
    return x * b.y - y * b.x;
  }

  real norm(void) const {
    return x * x + y * y;
  }

  real abs(void) const {
    return sqrt(norm());
  }

  real angle(void) const {
    return atan2(y, x);
  }
};

struct Vec3 {
  real x, y, z;

  void operator += (const Vec3 &b) {
    x += b.x;
    y += b.y;
    z += b.z;
  }

  void operator -= (const Vec3 &b) {
    x -= b.x;
    y -= b.y;
    z -= b.z;
  }

  void operator *= (real c) {
    x *= c;
    y *= c;
    z *= c;
  }

  void operator /= (real c) {
    x /= c;
    y /= c;
    z /= c;
  }

  friend Vec3 operator * (real c, const Vec3 &a) {
    return {a.x * c, a.y * c, a.z * c};
  }

  Vec3 operator + (void) const {
    return *this;
  }

  Vec3 operator - (void) const {
    return {-x, -y, -z};
  }

  DEF_OP(Vec3, const Vec3 &, +=, +)
  DEF_OP(Vec3, const Vec3 &, -=, -)
  DEF_OP(Vec3, real, *=, *)
  DEF_OP(Vec3, real, /=, /)

  // ----------------------------------------

  real dot(const Vec3 &b) const {
    return x * b.x + y * b.y + z * b.z;
  }

  Vec3 det(const Vec3 &b) const {
    return {y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x};
  }

  Vec3 unit(void) const {
    return *this / abs();
  }

  real norm(void) const {
    return x * x + y * y + z * z;
  }

  real abs(void) const {
    return sqrt(norm());
  }

  Vec3 perp(void) const {
    if (fabs(x) >= fabs(y) && fabs(x) >= fabs(z)) {
      real x2 = -(y + z) / x;
      return {x2, 1, 1};
    } else if (fabs(y) >= fabs(z)) {
      real y2 = -(x + z) / y;
      return {1, y2, 1};
    } else {
      real z2 = -(x + y) / z;
      return {1, 1, z2};
    }
  }
};

struct Line {
  Vec3 a, b;
};

struct Plane {
  Vec3 a, b;
};

struct CircleS {
  Vec3 o_surface, o_real;
  real r_surface, r_real;
  Vec3 B1, B2, B3;
  real angle, height;

  CircleS(void) {}

  CircleS(const Vec3 &o_s, real r_s) : o_surface(o_s), r_surface(r_s) {
    o_surface = o_surface.unit();
    B1 = o_surface.unit();
    B2 = B1.perp().unit();
    B3 = B1.det(B2);
    angle = r_surface;
    height = 1 - cos(angle);
    o_real = cos(angle) * o_surface;
    r_real = sin(angle);
  }

  real GetTheta(const Vec3 &p) const {
    // get angle of a point on circle
    // return real in [0, 2pi)
    // B2 -> 0, B3 -> pi/2

    Vec3 delta = p - o_real;
    real x = delta.dot(B2);
    real y = delta.dot(B3);
    real theta = atan2(y, x);
    if (fcmp(theta, 0) < 0) {
      theta += 2 * pi;
    }
    return theta;
  }

  Vec3 GetPoint(real theta) const {
    return (cos(theta) * B2 + sin(theta) * B3) * r_real + o_real;
  }

  Plane GetPlane(void) const {
    return {o_real, o_surface};
  }

  real Area(void) const {
    return 2 * pi * height;
  }

  void Reset(void) {
    *this = CircleS(o_surface, r_surface);
  }
};

Plane GetPlane(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
  return {a, (b - a).det(c - a)};
}

Vec2 LineIntersection(const Vec2 &u1, const Vec2 &v1, const Vec2 &u2, const Vec2 &v2) {
  // get intersection of 2d lines (u1 + v1 * t) and (u2 + v2 * t), t in R
  // v1, v2 must not be collinear
  // checked

  real t = (u2 - u1).det(v2) / v1.det(v2);
  return u1 + v1 * t;
}

Line PlaneIntersection(const Plane &P1, const Plane &P2) {
  // get intersection of two planes
  // P1.b, P2.b must not be collinear
  // checked

  Vec3 B1 = P1.b.unit(), B3 = B1.det(P2.b).unit(), B2 = B1.det(B3);
  Vec2 u1 = {P1.a.dot(B1), P1.a.dot(B2)};
  Vec2 u2 = {P2.a.dot(B1), P2.a.dot(B2)};

  Vec3 T1 = P1.b.det(B3), T2 = P2.b.det(B3);
  Vec2 v1 = {T1.dot(B1), T1.dot(B2)};
  Vec2 v2 = {T2.dot(B1), T2.dot(B2)};

  Vec2 res2d = LineIntersection(u1, v1, u2, v2);
  Vec3 res3d = B1 * res2d.x + B2 * res2d.y;

  return {res3d, B3};
}

real DirectedDist(const Plane &P, const Vec3 &a) {
  return (a - P.a).dot(P.b.unit());
}

Vec3 Foot(const Line &L, const Vec3 &p) {
  return (p - L.a).dot(L.b) * L.b / L.b.norm() + L.a;
}

real CosAngle(const Vec3 &a, const Vec3 &b) {
  return (a.norm() + b.norm() - (a - b).norm()) / (2 * sqrt(a.norm() * b.norm()));
}

real SinAngle(const Vec3 &a, const Vec3 &b) {
  return sqrt(a.det(b).norm() / (a.norm() * b.norm()));
}

real Angle(const Vec3 &d1, const Vec3 &d2) {
  const real L = pi / 4, R = pi * (3.0 / 4);

  real cos_a = CosAngle(d1, d2);
  real approx = Acos(cos_a);
  if (approx >= L && approx <= R) {
    return approx;
  }
  real sin_a = SinAngle(d1, d2);
  real angle = Asin(sin_a);
  if (approx < L) {
    return angle;
  } else {
    return pi - angle;
  }
}

real SphericalDist(const Vec3 &a, const Vec3 &b) {
  return Angle(a, b);
}

void LineSphereIntersection(const Line &L, int &cnt, Vec3 &key1, Vec3 &key2) {
  // key2 after key1 along the direction of L
  Vec3 h = Foot(L, {0, 0, 0});
  real d_sqr = 1 - h.norm();
  if (abs(d_sqr) <= eps_sqr) {
    cnt = 1;
    key1 = h;
  } else if (d_sqr > 0) {
    real coeff = sqrt(d_sqr / L.b.norm());
    cnt = 2;
    key1 = h - L.b * coeff;
    key2 = h + L.b * coeff;
  } else {
    cnt = 0;
  }
}

bool Contain(const CircleS &C1, const CircleS &C2) {
  real dist = SphericalDist(C1.o_surface, C2.o_surface);
  return fcmp(C1.r_surface, C2.r_surface + dist) >= 0;
}

Interval CoveredPart(const CircleS &C1, const CircleS &C2, Vec3 &key1, Vec3 &key2) {
  // return [-1, -1] if empty
  // (partly) checked

  real dist = SphericalDist(C1.o_surface, C2.o_surface);
  if (fcmp(C1.r_surface, C2.r_surface + dist) >= 0) {
    return {-1, -1};
  } else if (fcmp(C2.r_surface, C1.r_surface + dist) >= 0) {
    return {0, 2 * pi};
  }
  
  Plane P1 = C1.GetPlane();
  Plane P2 = C2.GetPlane();
  Line L = PlaneIntersection(P1, P2);

  int cnt_key;
  LineSphereIntersection(L, cnt_key, key1, key2);
  if (cnt_key < 2) {
    return {-1, -1};
  }

  return {C1.GetTheta(key1), C1.GetTheta(key2)};
}

Vec2 Foot(const Vec2 &u, const Vec2 &v, const Vec2 &p) {
  return (p - u).dot(v) * v / v.norm() + u;
}

void LineCircleIntersection(const Vec2 &u, const Vec2 &v, int &cnt, Vec2 &key1, Vec2 &key2) {
  Vec2 h = Foot(u, v, {0, 0});
  real d_sqr = 1 - h.norm();
  if (abs(d_sqr) <= eps_sqr) {
    cnt = 1;
    key1 = h;
  } else if (d_sqr > 0) {
    real coeff = sqrt(d_sqr / v.norm());
    cnt = 2;
    key1 = h - v * coeff;
    key2 = h + v * coeff;
  } else {
    cnt = 0;
  }
}

Interval CoveredPart2(const CircleS &C1, const CircleS &C2, Vec3 &res1, Vec3 &res2) {
  real dist = SphericalDist(C1.o_surface, C2.o_surface);
  if (fcmp(C1.r_surface, C2.r_surface + dist) >= 0) {
    return {-1, -1};
  } else if (fcmp(C2.r_surface, C1.r_surface + dist) >= 0) {
    return {0, 2 * pi};
  } else if (fcmp(C1.r_surface + C2.r_surface, dist) <= 0) {
    return {-1, -1};
  }

  Plane P = C2.GetPlane();
  Vec3 B2 = C1.B2, B3 = C1.B3;
  real a = B2.dot(P.b) * C1.r_real;
  real b = B3.dot(P.b) * C1.r_real;
  real c = (P.a - C1.o_real).dot(P.b);

  // a * cos(t) + b * sin(t) = c
  // ax + by = c, intersect with unit circle
  // direction: (-b, a)

  Vec2 u, v = {-b, a};
  if (abs(a) >= abs(b)) {
    u = {c / a, 0};
  } else {
    u = {0, c / b};
  }

  int cnt;
  Vec2 key1, key2;
  LineCircleIntersection(u, v, cnt, key1, key2);
  if (cnt < 2) {
    return {-1, -1};
  }

  real l = key1.angle(), r = key2.angle();
  if (fcmp(l, 0) < 0) l += 2 * pi;
  if (fcmp(r, 0) < 0) r += 2 * pi;
  res1 = C1.GetPoint(l);
  res2 = C1.GetPoint(r);
  return {l, r};
}

bool OnCircle(const CircleS &C, const Vec3 &a) {
  return IsZero(DirectedDist(C.GetPlane(), a)) &&
    IsZero((a - C.o_real).norm() - sqr(C.r_real));
}

bool InCircle(const CircleS &C, const Vec3 &a) {
  return fcmp(Angle(C.o_surface, a), C.angle) <= 0;
}

bool IsLeftHand(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
  return a.det(b).dot(c) > 0;
}

real SphericalLeftHandAngleSin(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
  Vec3 d1 = a.det(b), d2 = b.det(c);
  return SinAngle(d1, d2);
}

real SphericalLeftHandAngleCos(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
  Vec3 d1 = a.det(b), d2 = b.det(c);
  return CosAngle(d1, d2);
}

real SphericalLeftHandAngle(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
  // angle ABC is left-hand
  // return [0, pi], the outer angle
  const real L = pi / 4, R = pi * (3.0 / 4);

  Vec3 d1 = a.det(b), d2 = b.det(c);
  real cos_a = CosAngle(d1, d2);
  real approx = Acos(cos_a);
  if (approx >= L && approx <= R) {
    return approx;
  }
  real sin_a = SinAngle(d1, d2);
  real angle = Asin(sin_a);
  if (approx < L) {
    return angle;
  } else {
    return pi - angle;
  }
}

real SubL(const Vec3 &A, const Vec3 &B, const Vec3 &C) {
  real a = SphericalDist(B, C), b = SphericalDist(A, C);
  real cos_c = -SphericalLeftHandAngleCos(B, C, A);
  real sin_c = SphericalLeftHandAngleSin(B, C, A);
  return atan2((tan(a / 2) * tan(b / 2) * sin_c),
               (1 + tan(a / 2) * tan(b / 2) * cos_c)) * 2;
}

real SphericalLeftHandTriangleArea(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
  real A = SphericalDist(b, c), B = SphericalDist(c, a), C = SphericalDist(a, b);
  if (A <= B && A <= C) {
    return SubL(b, c, a);
  } else if (B <= C) {
    return SubL(c, a, b);
  } else {
    return SubL(a, b, c);
  }
}

real SphericalTriangleDirectedArea(const Vec3 &a, const Vec3 &b, const Vec3 &c) {
  return IsLeftHand(a, b, c) ?
    SphericalLeftHandTriangleArea(a, b, c) :
    -SphericalLeftHandTriangleArea(a, c, b);
}

real SphericalCircularSegmentArea(const CircleS &C, real l, real r, const Vec3 &spoint, const Vec3 &tpoint) {
  return C.Area() * (r - l) / (2 * pi) -
    SphericalTriangleDirectedArea(C.o_surface, spoint, tpoint);
}

real AreaBelowNorth(const CircleS &C, real l, real r, const Vec3 &spoint, const Vec3 &tpoint) {
  if (l == 0 && r == 2 * pi) {
    return C.Area() - 4 * pi;
  }

  real area_above = SphericalCircularSegmentArea(C, l, r, spoint, tpoint) +
    SphericalTriangleDirectedArea({0, 0, 1}, spoint, tpoint);

  real lt1 = atan2(spoint.y, spoint.x);
  real lt2 = atan2(tpoint.y, tpoint.x);

  while (fcmp(lt1, lt2) > 0) {
    lt2 += 2 * pi;
  }
  real area_moon = (lt2 - lt1) * 2;
  return area_above - area_moon;
}

real AreaBelowNormal(const CircleS &C, real l, real r, const Vec3 &spoint, const Vec3 &tpoint) {
  if (l == 0 && r == 2 * pi) {
    return C.Area();
  }
  return SphericalCircularSegmentArea(C, l, r, spoint, tpoint) +
    SphericalTriangleDirectedArea({0, 0, -1}, spoint, tpoint);
}

real AreaBelow(const CircleS &C, real l, real r, const Vec3 &spoint, const Vec3 &tpoint) {
  Vec3 north_pole = {0, 0, 1};
  if (InCircle(C, north_pole)) {
    return AreaBelowNorth(C, l, r, spoint, tpoint);
  } else {
    return AreaBelowNormal(C, l, r, spoint, tpoint);
  }
}

// ----------------------------------------

const int maxn = 5000;

int n;
CircleS circ[maxn], circ_bak[maxn];

void Rotate(real &x, real &y, real x2, real y2) {
  real x3 = x * x2 - y * y2, y3 = x * y2 + y * x2;
  x = x3;
  y = y3;
}

void RandomRotate(void) {
  real alpha = (real)rand() / RAND_MAX * (2 * pi);
  real beta = (real)rand() / RAND_MAX * (2 * pi);
  real cos_alpha = cos(alpha), sin_alpha = sin(alpha);
  real cos_beta = cos(beta), sin_beta = sin(beta);
  for (int i = 0; i < n; ++i) {
    Rotate(circ[i].o_surface.x, circ[i].o_surface.z, cos_alpha, sin_alpha);
    Rotate(circ[i].o_surface.y, circ[i].o_surface.z, cos_beta, sin_beta);
    circ[i].Reset();
  }
}

void RotateAll(real alpha, real beta) {
  copy(circ_bak, circ_bak + n, circ);
  real cos_alpha = cos(alpha), sin_alpha = sin(alpha);
  real cos_beta = cos(beta), sin_beta = sin(beta);
  for (int i = 0; i < n; ++i) {
    Rotate(circ[i].o_surface.x, circ[i].o_surface.z, cos_alpha, sin_alpha);
    Rotate(circ[i].o_surface.y, circ[i].o_surface.z, cos_beta, sin_beta);
    circ[i].Reset();
  }
}

real NorthDist(void) {
  real ans = pi / 2;
  Vec3 north = {0, 0, 1};
  for (int i = 0; i < n; ++i) {
    Min<real>(ans, abs(circ[i].r_surface - SphericalDist(circ[i].o_surface, north)));
  }
  return ans;
}

void AdjustInput(void) {
  sort(circ, circ + n, [](const CircleS &a, const CircleS &b) {
      return a.r_surface < b.r_surface;
    });
  int n2 = 0;
  for (int i = 0; i < n; ++i) {
    bool covered = false;
    for (int j = i + 1; j < n; ++j) {
      if (Contain(circ[j], circ[i])) {
        covered = true;
        break;
      }
    }
    if (!covered) {
      circ[n2++] = circ[i];
    }
  }
  n = n2;

  copy(circ, circ + n, circ_bak);
  real best_dist = -1;
  real alpha, beta;
  for (int i = 0; i < 40; ++i) {
    real a = RandomReal() * 2 * pi;
    real b = RandomReal() * 2 * pi;
    RotateAll(a, b);
    real d = NorthDist();
    if (d > best_dist) {
      best_dist = d;
      alpha = a;
      beta = b;
    }
  }
  RotateAll(alpha, beta);
}

const int maxev = maxn * 2;

struct Event {
  real t;
  int d;
  Vec3 point;
  bool operator < (const Event &b) const {
    return t < b.t;
  }
} ev[maxev];

int cntev;

real SubSolve(int u) {
  cntev = 0;
  int init = 0;
  for (int i = 0; i < n; ++i) {
    if (i == u) continue;
    Vec3 a, b;
    Interval I = CoveredPart2(circ[u], circ[i], a, b);
    if (I.l < 0) continue;
    if (I.l > I.r) ++init;
    ev[cntev++] = {I.l, 1, a};
    ev[cntev++] = {I.r, -1, b};
  }
  ev[cntev++] = {2 * pi, 1, circ[u].GetPoint(0)};
  sort(ev, ev + cntev);

  int cur = init;
  real empty_begin = 0;
  real ans = 0;
  Vec3 begin_point = circ[u].GetPoint(0);
  for (int i = 0; i < cntev; ++i) {
    if (ev[i].d == -1) {
      if (--cur == 0) {
        empty_begin = ev[i].t;
        begin_point = ev[i].point;
      }
    } else {
      if (++cur == 1) {
        ans += AreaBelow(circ[u], empty_begin, ev[i].t, begin_point, ev[i].point);
      }
    }
  }

  return ans;
}

real Solve(void) {
  AdjustInput();
  bool special = false;
  Vec3 north_pole = {0, 0, 1};
  for (int i = 0; i < n; ++i) {
    if (InCircle(circ[i], north_pole)) {
      special = true;
      break;
    }
  }
  real sum = special ? 4 * pi : (real)0;
  for (int i = 0; i < n; ++i) {
    sum += SubSolve(i);
  }
  return sum;
}

// ----------------------------------------

int main(void) {
  srand(time(NULL));

  int T;
  scanf("%d", &T);
  while (T--) {
    real R1, RG;
    scanf("%d", &n);
    ReadReal(R1);
    ReadReal(RG);
    for (int i = 0; i < n; ++i) {
      real x, y, z, r;
      ReadReal(x);
      ReadReal(y);
      ReadReal(z);
      ReadReal(r);
      r /= R1;
      circ[i] = CircleS({x, y, z}, r);
    }

    RG /= R1;
    CircleS example({0, 0, 1}, RG);
    real area = Solve();
    real tot = 4 * pi;
    real ans = area + (tot - area) * (example.Area() / tot);
    WriteReal(ans * R1 * R1);
    putchar('\n');
  }

  return 0;
}
