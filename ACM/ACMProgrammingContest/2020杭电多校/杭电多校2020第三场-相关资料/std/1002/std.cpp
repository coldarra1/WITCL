#include <bits/stdc++.h>
using namespace std;
long long n, N, L, R, sum, ans;
vector<pair<long long, long long>> v;
struct Queue
{
	deque<pair<long long, long long>> v;
	deque<pair<long long, long long>>::iterator p;
	void push(pair<long long, long long> x)
	{
		ans += x.first * x.second;
		while (p != v.end() && p->first < x.first)
			p++;
		if (p == v.end())
			v.push_back(x), p = --v.end();
		else
			p->second += x.second;
	}
} q;
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)
	{
		sum = ans = 0;
		v.clear();
		q.v.clear();
		scanf("%lld %lld %lld", &n, &L, &R);
		for (int i = 1; i <= n; i++)
		{
			long long x;
			scanf("%lld", &x);
			q.v.push_back({i, x});
			sum += x;
		}
		long long m = (sum - 1) / (R - 1) + ((sum - 1) % (R - 1) != 0);
		if (m * (L - 1) > sum - 1)
			printf("-1\n");
		else
		{
			if (R != L)
			{
				long long tmp = m * (R - 1) - (sum - 1);
				//printf("%lld----\n", tmp);
				long long d = tmp / (R - L);
				v.push_back({L, d});
				tmp -= d * (R - L);
				m -= d;
				//printf("%lld %lld----\n", tmp);
				if (tmp)
					v.push_back({R - tmp, 1}), m--;
			}
			if (m)
				v.push_back({R, m});
			q.p = q.v.begin();
			N = n;
			pair<long long, long long> now = {0, 0};
			for (auto t : v)
			{
				while (1)
				{
					if (now.second)
					{
						if (t.first - now.second > q.v.begin()->second)
						{
							now.second += q.v.begin()->second;
							now.first += q.v.begin()->second * q.v.begin()->first;
							q.v.pop_front();
							continue;
						}
						else
						{
							q.v.begin()->second -= t.first - now.second;
							now.first += (t.first - now.second) * q.v.begin()->first;
							now.second += t.first - now.second;
							t.second--;
							q.push({now.first, 1});
							now = {0, 0};
						}
					}
					long long d = min(t.second, q.v.begin()->second / t.first);
					q.push({t.first * q.v.begin()->first, d});
					t.second -= d;
					q.v.begin()->second -= d * t.first;
					if (!t.second)
						break;
					else
					{
						now.first += q.v.begin()->second * q.v.begin()->first, now.second += q.v.begin()->second;
						q.v.pop_front();
					}
				}
			}
			printf("%lld\n", ans);
		}
	}
	return 0;
}