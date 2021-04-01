# Kirakira

## Description

There are $n$ stars in the sky. At every moment, the $i$-th of them has a probability of $u_i/v_i(1 \leq u_i < v_i<P=31607)$ to become visible. All stars are independent of each other. The position of a star can be described as a coordinate on a 2D plane. No two stars share the same coordinate. Your task is to compute the expectation value of the area of the convex hull formed by the visible stars.
Formally, let $P = 31607$. It can be shown that the answer can be expressed as an irreducible fraction $p/q$, where $p$ and $q$ are integers and $q \not \equiv 0 \pmod{P}$. Output the integer equal to $p \cdot q^{-1} \bmod P$. In other words, output such an integer $x$ that $0 \le x < P$ and $x \cdot q \equiv p \pmod{P}$.

## Input

The first line contains a single integer $T$ ($1 \le T \le 100$), denoting the number of test cases.

For each test case, the first line contains a single integer $n$$(1 \le n \le 1000)$, denoting the number of stars.

Each of the following $n$ lines describes a stars. The $i$-th line of them contains 4 integers $x_i, y_i, u_i, v_i(-1000 \le x_i,y_i \le 1000, 1 \leq u_i < v_i<P=31607)$ indicating the coordinate of the $i$-th star and the probability of the $i$-th star to become visible. It is guaranteed that no two stars share the same coordinate.

There are at most $3$ test cases satisfying $n>20$.

## Output

Output the integer equal to $p \cdot q^{-1} \bmod P$ denoting the answer.

## Sample Input

```
2
4
0 0 1 2
1 0 1 2
0 1 1 2
1 1 1 2
4
0 0 1 2
1 0 1 2
-1 0 1 2
0 1 1 2
```

## Sample Output

```
21730
21730
```