# Little Rabbit's Equation

### 题目描述

Little Rabbit is interested in radix. In a positional numeral system, the radix is the number of unique digits, including the digit $0$, used to represent numbers. For example, for the decimal system (the most common system in use today) the radix is ten, because it uses the ten digits from $0$ to $9$. Generally, in a system with radix $b$ ($b > 1$), a string of digits $d_1 \dots d_n$ denotes the number $d_1b^{n−1} + d_2b^{n−2} + \dots + d_nb^0$, where $0 \le d_i < b$.

Little Rabbit casually writes down an equation. He wonders which radix this equation fits.

### 输入格式

The are several test cases. Each test case contains a string in a line, which represents the equation Little Rabbit writes down. The length of the string is at most $15$. The input is terminated by the end of file.

The equation's format: A number, an operator, a number, the equals sign `=`, and a number. There's no blank space in the string.

Each number has at least $1$ digit, which may contain digital numbers $0$ to $9$ or uppercase letters $A$ to $F$ (which represent decimal $10$ to $15$). The number is guaranteed to be a non-negative integer, which means it doesn't contain the radix point or negative sign. But the number may contain leading zeros. 

The operator refers to one of the basic elementary arithmetic operators, namely the plus sign `+`, the minus sign `-`, the multiplication sign `*`, or the division sign `/`. It is guaranteed that the number after the division sign will not be equal to $0$. Please note that the division here is not integer division. For example, in the decimal system, `7/2=3` is not correct.

### 输出格式

For each test case, output an integer $r$ ($2 \le r \le 16$) in a line, which means the equation is correct in the system with radix $r$. If there are multiple answers, output the minimum one. If there is no answer between $2$ and $16$, output $-1$.

### 输入样例

```
1+1=10
18-9=9
AA*AA=70E4
7/2=3
```
### 输出样例

```
2
10
16
-1
```
