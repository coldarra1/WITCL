题意：

轮流推动图中的两个条，保证它们相交且操作数最少

题解：

签到题，(n-a-1)/(b-a)*2+1

```c++
#include <stdio.h>

int n, a, b;

int main()
{
	scanf("%d %d %d", &a, &b, &n);
	printf("%d\n", (n-a-1)/(b-a)*2+1);
}

```

