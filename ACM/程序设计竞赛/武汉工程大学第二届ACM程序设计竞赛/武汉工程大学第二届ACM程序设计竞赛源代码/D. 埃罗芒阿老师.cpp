# include <iostream>
# include <algorithm>
 
using namespace std;
 
bool point_line(double x, double y, double a, double b, double c, double d)
{
	if (a == c)
		return x == a && y >= min(b, d) && y <= max(b, d);
	return (y - b == (d - b) / (c - a) * (x - a)) && x >= min(a, c) && x <= max(a, c) && y >= min(b, d) && y <= max(b, d);
}
 
bool x_line(double x, double y1, double y2, double a, double b, double c, double d)
{
	double y = (d - b) / (c - a) * (x - a) + b;
	return x >= min(a, c) && x <= max(a, c) && y >= min(y1, y2) && y <= max(y1, y2) && y >= min(b, d) && y <= max(b, d);
}
 
int main()
{
	int T;
	cin >> T;
	while (T--) {
		double a1, b1, c1, d1, a2, b2, c2, d2;
		cin >> a1 >> b1 >> c1 >> d1 >> a2 >> b2 >> c2 >> d2;
		bool success;
		// 输入的两组坐标完全相同
		if (a1 == a2 && b1 == b2 && c1 == c2 && d1 == d2 || a1 == c2 && b1 == d2 && c1 == a2 && d1 == b2)
			success = true;
		// 存在点的情况
		else if (a1 == c1 && b1 == d1 && a2 == c2 && b2 == d2)  // 两点坐标相同的判断可以也归入上面一个if
			success = a1 == a2 && b1 == b2;
		else if (a1 == c1 && b1 == d1 && (a2 != c2 || b2 != d2))
			success = point_line(a1, b1, a2, b2, c2, d2);
		else if ((a1 != c1 || b1 != d1) && a2 == c2 && b2 == d2)
			success = point_line(a2, b2, a1, b1, c1, d1);
		else {
			// 不存在点的情况
			if (a1 == c1 && a2 == c2)
				success = a1 == a2 && min(max(b1, d1), max(b2, d2)) >= max(min(b1, d1), min(b2, d2));
			else if (a1 != c1 && a2 == c2)
				success = x_line(a2, b2, d2, a1, b1, c1, d1);
			else if (a1 == c1 && a2 != c2)
				success = x_line(a1, b1, d1, a2, b2, c2, d2);
			else {
				// 两条均不垂直于x轴的线段
				if (b1 == d1 && b2 == d2)
					success = b1 == b2 && min(max(a1, c1), max(a2, c2)) >= max(min(a1, c1), min(a2, c2));
				else if ((d1 - b1) / (c1 - a1) == (d2 - b2) / (c2 - a2))
					success = (b1 - (a1 * (d1 - b1) / (c1 - a1)) == b2 - (a2 * (d2 - b2) / (c2 - a2))) && min(max(a1, c1), max(a2, c2)) >= max(min(a1, c1), min(a2, c2));
				else {
					double x = (b2 - b1 + a1 * (d1 - b1) / (c1 - a1) - a2 * (d2 - b2) / (c2 - a2)) / ((d1 - b1) / (c1 - a1) - (d2 - b2) / (c2 - a2));
					double y = (d1 - b1) / (c1 - a1) * x - a1 * (d1 - b1) / (c1 - a1) + b1;
					success = x >= min(a1, c1) && x <= max(a1, c1) && x >= min(a2, c2) && x <= max(a2, c2) && y >= min(b1, d1) && y <= max(b1, d1) && y >= min(b2, d2) && y <= max(b2, d2);
				}
			}
		}
		if (success)
			cout << "Hard" << endl;
		else
			cout << "Easy" << endl;
	}
	return 0;
}
