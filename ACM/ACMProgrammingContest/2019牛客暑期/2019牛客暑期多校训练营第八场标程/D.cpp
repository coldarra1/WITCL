#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define N 100000 + 5
#define INF 0x3f3f3f3f

const int Fx[6][3] = {{1, 0, 0}, {0, 1, 0}, {-1, 0, 0}, {0, -1, 0}, {0, 0, 1}, {0, 0, -1}};
int n, m, h, q, k, Dis[N];

struct Point
{
	int x, y, z;
	Point (int x, int y, int z) : x(x), y(y), z(z) {}
};

vector<Point> Cache, Bank, Q;

inline int Encode(int x, int y, int z)
{
	return (x - 1) * m * h + (y - 1) * h + z;
}

void BFS()
{
	for (int i = 1; i <= n * m * h; i ++)
		Dis[i] = INF;
	for (const Point &p : Bank)
		Dis[Encode(p.x, p.y, p.z)] = 0;
	Q = Bank;
	for (size_t t = 0; t < Q.size(); t ++)
	{
		int x = Q[t].x, y = Q[t].y, z = Q[t].z, c = Encode(x, y, z);
		for (int k = 0; k < 6; k ++)
		{
			int tx = x + Fx[k][0], ty = y + Fx[k][1], tz = z + Fx[k][2];
			if (tx && ty && tz && tx <= n && ty <= m && tz <= h && Dis[Encode(tx, ty, tz)] == INF)
			{
				Dis[Encode(tx, ty, tz)] = Dis[c] + 1;
				Q.emplace_back(tx, ty, tz);
			}
		}
	}
}

int main()
{
	scanf("%d%d%d%d", &n, &m, &h, &q);
	for (int i = 1; i <= n * m * h; i ++)
		Dis[i] = INF;
	k = 3 * int(sqrt(n * m * h));
	for (int i = 1, op, x, y, z; i <= q; i ++)
	{
		scanf("%d%d%d%d", &op, &x, &y, &z);
		if (op == 1)
		{
			Cache.emplace_back(x, y, z);
			if (Cache.size() == k)
			{
				Bank.insert(Bank.end(), Cache.begin(), Cache.end());
				Cache.clear();
				BFS();
			}
		}
		else
		{
			int ans = Dis[Encode(x, y, z)];
			for (const Point &p : Cache)
				ans = min(ans, abs(p.x - x) + abs(p.y - y) + abs(p.z - z));
			printf("%d\n", ans);
		}
	}
	return 0;
}
