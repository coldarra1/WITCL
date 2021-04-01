# Very Easy Graph Problem
##### TimeLimit: 1000MS, MemoryLimit: 256MiB

 A graph has $n$ dots and $m$ edges，The $i$-th edge’s length is $2^i$，every dots has a color ,which is either white or black.The question is ask you to calculate $\sum\limits_{i=1}^{n}\sum\limits_{j=1}^{n}shortest\_distance(i,j)*(a_i==1\&\&a_j==0)$
 
 
 Because the answer may be too large, please output the answer after taking the model of $10^9 + 7$。

## Standard Input
The first line contains one ingeter $T$
The second line contains two ingeters $n,m$($1\le n\le 10^5,1\le m\le 2*10^5$)

The third line contains $n$ positive integers $a_1,a_2,...,a_n(a_i = 0$ or $1$) ——
the color of the dots,$a_i=1$ means color is black,else color is white.

The follow $m$ lines contain two ingeter $u,v(1
\le u,v \le n)$,and the $i$-th line represent the undirected edge’s length is $2^i$,between dot $u$ and $v$.

The sum of n,m is less than 1e6.
## Standard Output
Print a single integer--the value of the formula model $10^9+7$.