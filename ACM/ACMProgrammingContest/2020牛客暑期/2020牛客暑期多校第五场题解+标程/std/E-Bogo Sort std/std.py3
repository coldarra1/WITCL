n = int(input())
a = [0] + list(map(int, input().split()))
vis = [False] * (n + 1)
loop = []
for i in range(1, n + 1):
    if not vis[i]:
        x = i
        cnt = 0
        while not vis[x]:
            cnt += 1
            vis[x] = True
            x = a[x]
        loop.append(cnt)
for i in range(1, n + 1):
    a[i] = 0
for x in loop:
    i = 2
    while i * i <= x:
        if x % i == 0:
            cnt = 0
            while x % i == 0:
                cnt += 1
                x //= i
            a[i] = max(a[i], cnt)
        i += 1
    if x > 1:
        a[x] = max(1, a[x])
ans = 1
for i in range(2, n + 1):
    while a[i] > 0:
        ans *= i
        a[i] -= 1
print(ans)