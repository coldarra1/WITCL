原命题等价于：对于任意的 $b$ 进制正整数 $y = \overline{c_1 c_2 \cdots c_n}$，如果 $c_1 + c_2 + \cdots + c_n \equiv 0 \pmod{x}$，那么 $y \equiv 0 \pmod{x}$，否则 $y \not\equiv 0 \pmod{x}$。

上述命题成立当且仅当 $b \equiv 1 \pmod{x}$。

证明：

* 当 $b \equiv 1 \pmod{x}$ 时，有 $y \equiv c_1 b^{n-1} + c_2 b^{n-2} + \cdots + c_n b^0 \equiv c_1 + c_2 + \cdots + c_n \pmod{x}$，于是上述命题成立。
* 当 $b \not\equiv 1 \pmod{x}$ 时，假设上述命题成立，有：
    * 若 $x \leq b$，令 $y = 1 \cdot b^1 + (x-1) b^0$，则应有 $y \equiv b + x - 1 \equiv 0 \pmod{x}$，即 $b \equiv 1 \pmod{x}$，但此时 $b \not\equiv 1 \pmod{x}$，出现矛盾，于是上述命题不成立。
    * 若 $x > b$，令 $y = x = \overline{c_1 c_2 \cdots c_n}$，显然 $c_1 + c_2 + \cdots + c_n \not\equiv 0 \pmod{x}$，于是 $y \not\equiv 0 \pmod{x}$，但 $y \equiv 0 \pmod{x}$，出现矛盾，于是上述命题不成立。

综上，上述命题成立当且仅当 $b \equiv 1 \pmod{x}$。

