#include <bits/stdc++.h>

struct Point {
  int x, y;

  Point(int x = 0, int y = 0) : x(x), y(y) {}
};

Point operator-(Point a, const Point &b) { return Point(a.x - b.x, a.y - b.y); }

long long det(const Point &a, const Point &b) {
  return 1LL * a.x * b.y - 1LL * a.y * b.x;
}

std::istream &operator>>(std::istream &in, Point &p) {
  return in >> p.x >> p.y;
}

int main() {
  Point p[3];
  while (std::cin >> p[0] >> p[1] >> p[2]) {
    std::cout << std::abs(det(p[1] - p[0], p[2] - p[0])) * 11 << std::endl;
  }
}
