<center>
    Expectation
</center>



## $Time \, Limits: 10s$

## $Memory \, Limits: 512MB$



## $Description:$

You are given an undirected graph consisting of $n$ vertices with $m$ weighted edges. We define the weight of a spanning tree as the bitwise AND of all edges' weight in spanning tree.

Now We randomly select a spanning tree, you should calculate the expected value of the weight of this spanning tree. You are required to print the result mod $998244353$. $i.e.$, print $x \times y^{-1}$ mod $998244353$ where $x \times y ^ {-1}$ is the irreducible fraction representation of the result.



## $Input:$

The first line is an integer $t(1 \leq t \leq 10)$, the number of test cases.

For each test case, there is two space - separated integers $n(2 \leq n \leq 100)$ and $m(1 \leq m ≤ 1e4)$ in the first line, meaning the number of nodes in graph and the number of edges.

Then follows $m$ lines, each containing integers $u, v, w(1 \leq u, v, \leq n, 1 \leq w \leq 1e9, u \neq v)$, space separated, denoting an weight edge between $u$ and $v$ has weight $w$.



## $Output:$

For each test case, output a single line with a single integer, the answer.



## $Sample:$

| $input$                                       | $output$ |
| --------------------------------------------- | -------- |
| 1<br />3 3 <br />1 2 1 <br />1 3 1<br />2 3 1 | 1        |

