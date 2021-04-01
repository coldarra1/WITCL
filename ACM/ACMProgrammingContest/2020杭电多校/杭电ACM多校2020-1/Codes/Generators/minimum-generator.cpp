#include <bits/stdc++.h>
using namespace std;

const int N = 1100000;
const int P = 1e9 + 7;

int d[N];

inline int rnd() {
	return (rand() << 15) | rand();
}

inline int next_int(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

int main() {
	freopen("input.txt", "w", stdout);
	srand(time(0));
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	for (int i = 0; i < 10; i++) {
		int n = next_int(50001, 100000);
		while (n--) putchar('a' + rnd() % 26);
		puts("");
	}
	for (int i = 0; i < 10; i++) {
		int n = next_int(50001, 100000);
		while (n--) putchar('a' + rnd() % 2);
		puts("");
	}
	for (int i = 0; i < 1<<10; i++) {
		for (int j = 0; j < 11; j++) {
			if (i >> (10 - j) & 1) putchar('b');
			else putchar('a');
		}
		puts("");
	}
	for (int i = 0; i < 5000; i++) {
		int n = 100;
		for (int j = 0; j < n; j++) putchar('a' + rnd() % 2);
		puts("");
	}
	for (int i = 0; i < 500; i++) {
		int n = 1000;
		for (int j = 0; j < n; j++) putchar('a' + rnd() % 2);
		puts("");
	}
	for (int runs = 0; runs < 10; runs++) {
		int n = runs < 9 ? next_int(50000, 1000000) : 1000000;
		int len = 5;
		string s;
		for (int i = 0; i < len; i++) s.push_back(rnd() % 2 + 'a');
		int times = 0;
		while (s.length() < n) {
			times++;
			if (times >= 15) break;
			int cnt = next_int(0, (n - 1 - s.length()) / s.length());
			int len = s.length();
			for (int j = 0; j < cnt; j++) s += s.substr(0, len);
			int add = next_int(1, min(n - (int)s.length(), len));
			s += s.substr(0, add);
		}
		puts(s.c_str());
	}
	for (int runs = 0; runs < 10; runs++) {
		int n = runs < 9 ? next_int(50000, 1000000) : 1000000;
		int len = 20;
		string pat;
		pat.push_back(rand() % 26 + 'a');
		pat.push_back(rand() % 26 + 'a');
		string s;
		for (int i = 0; i < len; i++) s.push_back(pat[rnd() % 2]);
		int times = 0;
		while (s.length() < n) {
			times++;
			if (times >= 100) break;
			int len = s.length();
			int lim = (n - 1 - len) / len;
			if (lim) s += s.substr(0, len);
			int add = next_int(1, min(n - (int)s.length(), len));
			s += s.substr(0, add);
		}
		puts(s.c_str());
	}
	for (int runs = 0; runs < 10; runs++) {
		int len = 10;
		string s;
		for (int i = 0; i < len; i++) s.push_back(rnd() % 2 + 'a');
		int n = runs < 9 ? next_int(50000, 100000) : 1000000;
		int times = 0;
		while (s.length() < n && ++times <= 10) {
			int add = next_int(1, min(n - (int)s.length(), (int)s.length()));
			int cnt = next_int(1, (n - s.length()) / add);
			for (int j = 0; j < cnt; j++) s += s.substr(0, add);
		}
		puts(s.c_str());
	}
	for (int i = 0; i < 1000000; i++) putchar('a');
	puts("");
	for (int i = 0; i < 1000000; i++) putchar('a' + i % 2);
	puts("");
	return 0;
}
