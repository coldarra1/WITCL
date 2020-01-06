# include <iostream>
# include <cstdio>
# include <vector>
# include <unordered_map>
# include <algorithm>
 
using namespace std;
 
const int maxn = 1e5 + 5;
const int Hash = 99991;
unordered_map<int, vector<int>> v;  // 以第一关键字为整个六芒星的hash值的所有六芒星的编号
 
struct Star {
	int nums[10][10]; // nums[i][j] : 第i个角的6个伤害浮动值   nums[i][0] : 第i个角的hash值
}s[maxn];
 
bool check_indoor(int *a, int *b)
{
	sort(a + 1, a + 1 + 6);
	sort(b + 1, b + 1 + 6);
	for (int i = 1; i <= 6; i++)
		if (a[i] != b[i])
			return false;
	return true;
}
 
bool check_outdoor(Star a, Star b)
{
	int cnt = 0;
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			if (a.nums[i][0] == b.nums[j][0] && check_indoor(a.nums[i], b.nums[j]))
				cnt++;
		}
	}
	return cnt == 6;
}
 
int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		int Sum = 0;
		for (int j = 1; j <= 6; j++) {
			int sum = 0;
			for (int k = 1; k <= 6; k++) {
				scanf("%d", &s[i].nums[j][k]);
				sum = (sum + s[i].nums[j][k]) % Hash;
			}
			s[i].nums[j][0] = sum;
			Sum = (Sum + sum) % Hash;
		}
		v[Sum].push_back(i);
	}
	bool success = true;
	for (int i = 1; i <= n; i++) {
		// 每个六芒星内部是否满足要求
		for (int j = 1; j < 6; j++) {
			for (int k = j + 1; k <= 6; k++)
				if (s[i].nums[j][0] == s[i].nums[k][0] && check_indoor(s[i].nums[j], s[i].nums[k])) {
					success = false;
					break;
				}
			if (!success)
				break;
		}
		if (!success)
			break;
	}
	if (success)
		// 六芒星之间是否满足要求
		for (auto x : v) {
			if (x.second.size() > 1) {
				for (int i = 0; i < x.second.size() - 1; i++) {
					for (int j = i + 1; j < x.second.size(); j++)
						if (check_outdoor(s[x.second[i]], s[x.second[j]])) {
							success = false;
							break;
						}
					if (!success)
						break;
				}
			}
			if (!success)
				break;
		}
	if (success)
		printf("SUCCESS!\n");
	else
		printf("BUG!\n");
	return 0;
}
