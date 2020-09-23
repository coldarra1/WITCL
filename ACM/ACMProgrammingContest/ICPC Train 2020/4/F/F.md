# Foreach

显然，当$t$中的某个值在$s$中没有出现过时，不存在答案。同样，由于第一种运算将会使$a$中的两个元素相同，所以如果$a,b$不相等且$b$中所有元素互不相等时，本题同样没有答案，此时输出$-1$即可。

在其他情况下，我们可以通过以下操作来构造答案：

- 将某个值$val_s$第一次出现的位置替换为数组中的任何其他元素$val_t$。
- 将最后一个元素替换为数组中的任何其他元素$val_t$。

第一种操作可以通过先对$val_s$调用第一种运算，再对$val_t$调用第二种运算来实现。

第二种操作可以通过对任意一个在当前$a$中没有出现的元素调用第一种运算，再对$val_t$调用第二种运算来实现。

我们考虑从$a_{n-2}$到$a_0$将$a$中的元素从$s$转变为$t$。（由于第二种操作的存在，最后一个元素可以在最后一次操作时特殊处理）你需要先将该元素保存到最后一个位置（为了不失去所有必要的值），并且用其他元素替换所有在当前位置之前且与当前位置值相等的元素。

但是，如果最后一个元素的值是唯一的，那么在以上操作之后仍然会导致失去一个必要的值。为了防止这种情况的发生，我们需要在当前处理的位置$i$之前，在$s$中找到任意一个不唯一的值（或者已经不会在$t_0$到$t_{i-1}$中出现的值），并将其中第一次出现的位置利用第一种操作改为$a_{n-1}$。

但是我们并不是总能找到这样的一个值。为了避免这种情况，可以考虑将最靠前的非唯一元素替换为第一个元素的值来改变最终数组$t$得到$t'$，并先令$a$变为$t'$，再从$t'$变为$t$。（当出现找不到这样一个值的时候，那么所有$a_0$到$a_{i-1}$和$a_{n-1}$一定互不相等，又因为其中又不存在不会出现在$t_0$到$t_{i-1}$和$t_{n-1}$这几个位置的值，所以此时$a_0$到$a_{i-1}$和$a_{n-1}$与$t_0$到$t_{i-1}$和$t_{n-1}$实际上值是一一对应的（就比如（3，1，4，5）和（5，1，3，4））所以当找到$t$中第一个非唯一元素将其改为$t_0$后，$a_0$到$a_{i-1}$和$a_{n-1}$与$t_0$到$t_{i-1}$和$t_{n-1}$一定形如（3，1，4，t0，5）与（5，1，3，t0，4）（（3，1，4，5，5）与（5，1，3，5，4）），此后每一步可以很容易证明不会出现找不到这样一个值的情况）

令第一个位置，$t$与$t'$中不相等的位置，最后一个位置的值分别为$[x,x,y]$，我们需要在最后将$t'$变为$t$，需要将其转化为$[x,z,y]$。则可以通过以下操作序列来完成：$[x,x,y] ->[y,x,y]->[y,x,x]->[y,y,x]->[x,y,y]->[x,z,y]$。



$Std:$

```c++
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

int main() {
//  freopen("in", "r", stdin);
	int n;
	scanf("%d", &n);
	vector<int> a(n), b(n);
	for (int &x: a) {
		scanf("%d", &x);
	}
	for (int &x: b) {
		scanf("%d", &x);
	}
	if (a == b) {
		printf("0\n");
		return 0;
	}
	set<int> required(b.begin(), b.end());
	if ((int)required.size() == n) {
		printf("-1\n");
		return 0;
	}
	for (int x : b) {
		if (find(a.begin(), a.end(), x) == a.end()) {
			printf("-1\n");
			return 0;
		}
	}
	vector<pair<int, int>> ops;
	int trash = 1;
	while (find(a.begin(), a.end(), trash) != a.end()) {
		trash++;
	}

  int rep = -1;
  for (int i = 0; i < n; i++) {
    if (find(b.begin() + i + 1, b.end(), b[i]) != b.end()) {
      rep = i;
      break;
    }
	}
  int rep_backup = b[rep];
  b[rep] = b[0];


	auto save_back = [&](int prefix) {
		if (required.count(a.back()) && find(a.begin(), a.begin() + prefix, a.back()) == a.begin() + prefix) {
			int req = 0;
			map<int, int> found;
			while (req < prefix && required.count(a[req])) {
				if (found.find(a[req]) != found.end()) {
					req = found[a[req]];
					break;
				}
				found[a[req]] = req;
				req++;
			}
			assert(req < prefix);
			ops.emplace_back(a[req], a.back());
			a[req] = a.back();
		}
	};

	save_back(n - 1);
	for (int i = n - 2; i >= 0; i--) {
		if (a[i] != b[i]) {
			int other = 0;
			while (other < n && a[other] == a[i]) {
				other++;
			}
			assert(other < n);
			for (int j = 0; j < i; j++) {
				if (a[j] == a[i]) {
					ops.emplace_back(a[j], a[other]);
					a[j] = a[other];
				}
			}
			if (a.back() != a[i]) {
				ops.emplace_back(trash, a[i]);
				a.back() = a[i];
			}
			ops.emplace_back(a[i], b[i]);
			a[i] = b[i];
		}
		required.erase(b[i]);
		if (i) {
      save_back(i);
    }
	}
	if (a.back() != b.back()) {
	   ops.emplace_back(trash, b.back());
  }
	if (rep != 0) {
                                               // b[0], b[0], b[end]
	  ops.emplace_back(b[0], b.back());          // b[end], b[0], b[end]
    assert(b[rep] == b[0]);
    assert(find(b.begin(), b.begin() + rep, b.back()) == b.begin() + rep);
    ops.emplace_back(trash, b[rep]);           // b[end], b[0], b[0]
    ops.emplace_back(b[rep], b.back());        // b[end], b[end], b[0]
    ops.emplace_back(b.back(), b[0]);          // b[0], b[end], b[0]
    ops.emplace_back(trash, b.back());         // b[0], b[end], b[end]
    ops.emplace_back(b.back(), rep_backup);    // b[0], b[end], b[end]
	}

	printf("%d\n", 2 * (int)ops.size());
	for (auto x : ops) {
		printf("foreach ($a as &$x) if ($x == %d) break;\n", x.first);
		printf("foreach ($a as  $x) if ($x == %d) break;\n", x.second);
	}
}
```

