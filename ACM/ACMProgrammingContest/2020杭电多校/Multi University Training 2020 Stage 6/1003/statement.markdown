##### Memory LImit : 256M, Time Limit: 1000MS

## Borrow
  Alice, Bob and Cindy are good friends. They go shopping together and buy the same. However, they don't bring the same units money with themselves so one of them suggests that the one with the most money should borrow 1 unit money to someone else with equal probability. That is to say, if they have $x, y, z(x \ge y \ge z)$ units money separately, the one with $x$ units money (if multiple people have the most then they decide one should borrow with equal probability) will give 1 unit to one of his/her friends with equal probability. After that, they have $x - 1, y + 1, z$ or $x - 1, y, z + 1$ units money.


  This act will last until everyone has the same units money. Three smart guys want to know the expected times of this act or if this situation will never come.

### Standard Input
The input contains several test cases.
The first line contains a single integer $T$, indicating the number of test cases.
Following $T$ lines, each line contains three integer $x, y, z$ indicating the money of three guys.

### Standard Output

For each test case, if the situation that everyone has the same units money will never come then print $- 1$, else print the expected times in a line. If the expected times is $\frac{P}{Q}$, you should output $P\cdot Q^{-1}\bmod 998244353$, where $Q^{-1}$ denotes the multiplicative inverse of $Q$ modulo $998244353$.

### Sample Input
3
1 2 3
1 1 4
5 1 4

### Sample Output
2
3
-1

### Constraints
$x + y + z \le 1e6, \sum{x + y + z} \le 3e6$



