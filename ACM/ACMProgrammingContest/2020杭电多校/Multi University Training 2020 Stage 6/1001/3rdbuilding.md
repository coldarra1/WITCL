# Road To The 3rd Building

## Description

Because of the thriller adventure game *The 3rd Building*, there are fewer and fewer students who would like to go to the 3rd Building. So few students are working in the studio in the 3rd Building. Students are even more reluctant to go to the 3rd Building for experiments, which are also annoying.

Kanade takes responsibility to improve this status. She thinks it a good idea to decorate the ginkgo trees along the road to the 3rd Building, making them cute. There are $n$ ginkgo trees that are planted along the road, numbered with $1\ldots n$. Each tree has a cute value. The cute value of tree $i$ is $s_i$.

Kanade defines a **plan** as an ordered pair $(i,j)$, here $1\le i\le j\le n$. It means a student will appear at the position of the tree $i$ magically, walk along the road, and finally stop walking at the position of the tree $j$. The **cute level** of a plan is the average of the cute value of the trees visited. Formally, the cute level of plan $(i,j)$ is $\frac{1}{j-i+1}\sum_{k=i}^j s_k$.

Kanade wants to know the mathematical expectation of the cute level if a student will take a plan among all these plans in a uniformly random way. But she is busy with learning Computer Networking, would you help her?

## Input

The first line of the input contains an integer $T$ — the number of testcases. You should process these testcases independently.

The first line of each testcase contains an integer $n$ — the number of ginkgo trees.

The second line of each testcase contains $n$ integers $s_i$ — the cute value of each ginkgo tree, space-separated.

$1\le T\le 20,1\le n\le 2\times 10^5,1\le s_i\le 10^9$

It is guaranteed that $\sum n\le 10^6$.

## Output

For each testcase, output the answer in the fraction form modulo $10^9+7$ in one line. That is, if the answer is $\frac{P}{Q}$, you should output $P\cdot Q^{-1}\bmod (10^9+7)$, where $Q^{-1}$ denotes the multiplicative inverse of $Q$ modulo $10^9+7$.

## Sample

### Sample Input

```plain
3
3
1 3 2
6
1 1 4 5 1 4
9
7325 516 56940 120670 16272 15007 337527 333184 742294
```

### Sample Output

```plain
83333336
188888893
303405448
```

## Hint

The answer to the first testcase is $\frac{25}{12}$.