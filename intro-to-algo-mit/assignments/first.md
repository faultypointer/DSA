# Problem Set 1

## Problem 1-1 Asymptotic Practice

*For each group of functions, sort the functions in increasing order of asymptotic (big-O) complexity:*

### Group 1

- $f_1(n) = n^{0.999999}logn$
- $f_2(n) = 10000000n$
- $f_3(n) = 1.000001^n$
- $f_4(n) = n^2$

#### Rough

$f_1$ is not exactly $n\log(n)$ and $f_2$ is linear so out of these two I don't know which
is less but these two are less than $f_4$ which is quadratic which in turn is less than $f_3$
which is exponential.

So $f_1?f_2 \lt  f_4 \lt f_3$

$$
    \frac{f_1(n)}{f_2(n)}\ = \frac{n^{0.99999}\log(n)}{1000000n}\\
    = \frac{\log(n)}{1000000n^{0.000001}}
$$
As $n \to \infin$ the rate of growth of $\log(n)$ is much slower than $n^{0.000001}$ so $f_1 \lt f_2$

#### Answer

$f_1 \lt f_2 \lt f_4 \lt f_3$

### Group 2

- $f_1(n) = 2^{2^{1000000}}$
- $f_2(n) = 2^{100000n}$
- $f_3(n) = {n \choose 2}$
- $f_4(n) = n \sqrt n$

#### Rough

$f_1$ is constant, $f_2$ is exponential, $f_3$ is
$$
\begin{align*}
    f_3(n) &= {n \choose 2} \\
           &= \frac{n!}{2!(n-2)!} \\
           &= \frac{n(n-1)}{2}
\end{align*}
$$

which is basically $n^2$ and finally $f_4$ is $n^{1.5}$.

#### Answer

$f_1 \lt f_4 \lt f_3 \lt f_2$.

### Group 3

- $f_1(n) = n^{\sqrt n}$
- $f_2(n) = 2^n$
- $f_3(n) = n^{10}.2^{n/2}$
- $f_4(n) = \displaystyle{\sum_{i=1}^{n}(i+1)}$

#### Rough

$f_4$ is quadratic, $f_3$ is definitely less than $f_2$ and I am confused about $f_1$.
It is most likely greater than all of them.
I think i'm wrong. After taking log, $f_3$ has the largest growth rate then its $f_2$ and
$f_1$. And I'm wrong again, about $f_2$ and $f_3$ (my initial guess was right).

#### Answer

$f_4 \lt f_1 \lt f_3 \lt f_2$

## Problem 1-2 Recurrence Relation Resolution

*For each of the following recurrence relations, pick the correct asymptotic runtime:*

### Group A

Select the correct asymptotic complexity of an algorithm with runtime $T(n, n)$ where
$$
\begin{align*}
&T(x, c) = \Theta (x) &\ for\ c \le 2 \\
&T(c, y) = \Theta (y) &\ for\ c \le 2 \\
&T(x, y) = \Theta (x+y) + T(x/2, y/2) &\ \\
\end{align*}
$$
*Options*

1. $\Theta (\log n)$
2. $\Theta (n)$
3. $\Theta (n \log n)$
4. $\Theta (n \log^2 n)$
5. $\Theta (n^2)$
6. $\Theta (2^n)$

#### Rough

Expanding the main recurrence relation, we get
$$
T(x, y) = \Theta(x+y) + \Theta(\frac{x+y}{2}) + \Theta(\frac{x+y}{4}) + ...
$$
This sequence is bounded from above by $2 \Theta (x+y)$ and from below by $\Theta(x+y)$. so the
asymptotic complexity of $T(n, n)$ is $\Theta(n)$.

#### Answer

$2. \ \Theta (n)$

### Group B

Select the correct asymptotic complexity of an algorithm with runtime $T(n, n)$ where
$$
\begin{align*}
&T(x, c) = \Theta (x) &\ for\ c \le 2 \\
&T(c, y) = \Theta (y) &\ for\ c \le 2 \\
&T(x, y) = \Theta (x+y) + T(x, y/2) &\ \\
\end{align*}
$$
*Options*

1. $\Theta (\log n)$
2. $\Theta (n)$
3. $\Theta (n \log n)$
4. $\Theta (n \log^2 n)$
5. $\Theta (n^2)$
6. $\Theta (2^n)$
