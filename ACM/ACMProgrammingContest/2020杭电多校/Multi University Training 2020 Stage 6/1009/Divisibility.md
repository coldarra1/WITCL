### Divisibility

You are given two $10$-based integers $b$ and $x$, and you are required to determine the following proposition is true or false:

For arbitrary $b$-based positive integer $y = \overline{c_1 c_2 \cdots c_n}$ ($c_i$ is the $i$-th dight from left of $y$), define $\displaystyle f(y) = \sum_{i=1}^n c_i$, if $\underbrace{f( f( \cdots f(y) \cdots ))}_{\infty}$ can be divided by $x$, then $y$ can be divided by $x$, otherwise $y$ can't be divided by $x$.

#### Standard Input

The first line contains a $10$-based integer $t\ (1 \leq t \leq 10^5)$ — the number of test cases.

For each test case, there is a single line containing two $10$-based integers $b$ and $x \ (2 \leq b,x \leq 10^{18})$.

#### Standard Output

For each test case, if the proposition is true, print "T", otherwise print "F" (without quotes).

#### Samples

| Input       | Output |
| ----------- | ------ |
| 1<br />10 3 | T      |

