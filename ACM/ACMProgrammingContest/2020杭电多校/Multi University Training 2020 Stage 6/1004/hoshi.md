# Asteroid in Love

## Description

During the summer vacation, the geoscience community launched a constellation observation activity.

On a clear night, Mira and Ao set up their telescopes. Through the telescopes, they observed $n$ stars. These $n$ stars could be regarded as points on a two-dimensional plane, with coordinates $(x_i, y_i)$.

It was boring to observe the stars alone, so they classified these stars into three categories according to their spectrum: R-type stars, G-type stars, and B-type stars.

Now, Mira wants to form a constellation named after Ao, for Ao to make up for the regret that there is no star named after Ao. This constellation should be small and beautiful. She wants the number of stars to be the least in this constellation. Besides, she wants the constellation contains all types of stars. It is easy to know that this constellation has only three stars, and the types of these three stars are R type, G type, and B type.

She also wants the area of the convex polygon enclosed by the stars of this constellation is the largest, that is, the area of the triangle formed by these three stars is the largest. If the triangle is trivial (that is, the three points that make up the triangle are on the same straight line), the area of the triangle is considered to be $0$.

Please tell Mira the largest area of Constellation Ao.

## Input

The first line contains an integer $T$, indicating the number of testcase.

For each testcase, the first line contains a positive integer $n$, indicating the number of stars observed.

From line $2$ to line $n + 1$, each line contains three integers $x, y, c$. Line $i$ describes the information of the stars $i-1$, where $x, y$ are the horizontal and vertical coordinates of the star's position, that is, the coordinates of the star are $(x, y)$; $c$ is for the description of stellar types, $0$ indicates that the stars are B-type stars, $1$ indicates R-type stars, and $2$ indicates G-type stars.

$T\le 10, 3\le n\le 3\times 10^3,|x|,|y|\le 10^9,0\le c\le 2$

It is guaranteed that there exists a Constellation Ao, and any two stars will not be in the same position.

## Output

For each testcase, output one real number per line indicates the maximum area. The answer should be rounded to one decimal place.

## Sample

### Sample Input

```plain
2
8
3 1 0
-5 3 0
-1 1 1
-1 -1 0
-2 1 0
2 -4 0
1 1 0
7 7 2
17
-5 1 0
-4 1 0
-3 1 0
-2 1 0
-1 1 0
0 1 0
1 1 0
2 1 0
3 1 0
4 1 0
5 1 0
-2 3 1
-4 2 1
7 5 1
9 1 2
7 3 2
-1 3 2
```

### Sample Output

```plain
29.0
28.0
```

