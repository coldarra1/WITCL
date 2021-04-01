2s , 3s for java
64MB, 128MB for java

Description:

Many people love numbers, and some have a penchant for specific numbers. Nowadays in popular culture, 1145141919 is a very fragrant number, and many people want to represent all other numbers with this number.

Let $S$ be an infinite string of "1145141919" infinitely stitched together as "114514191911451419191145141919...".

Take a prefix $T$ of $S$ , you can insert '$($' , '$)$' , '$+$' or '$*$' to $T$ to form a new string $T'$, and then let the value of $T'$ be $val(T')$ according to ordinary rules. (You can insert any number of operators, even 0. But need to ensure that the inserted operators form legitimate operations)

Now for a number $N$, please calculate the minimum length of $T$ that can make $val(T')=N$. For example, when $N=520$, the minimum length of $6$ (pick the first $6$ characters $114514$ and insert operators to make $T'=1+1+4+514$ , then we have $val(T')=520$ )

If no such $T$ exists, output $-1$.

Input:

There are multiple test cases.

The first line with a number $t$ indicates the number of test cases.

For each test case, one integer $N$ per line indicates an inquiry.

$1\le t\le 30$

$1\le N\le 5000$

Output:

Output $t$ lines.

One integer per line indicates the corresponding answer.

Sample input:

    3
    520
    1
    2

Sample output:

    6
    1
    2