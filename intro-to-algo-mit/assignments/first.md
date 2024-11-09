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
&T(x, y) = \Theta (x) + T(x, y/2) &\ \\
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

Rewriting the relation to avoid $\Theta$ notation, and expanding
$$
T(x, y) = \underbrace{cx + cx + cx + cx + ... + cx}_{\Theta (\log y)\ times}
$$
so $T(x, y) = \Theta(x \log y)$

#### Answer

$3. \Theta(n \log n)$

### Group C

Select the correct asymptotic complexity of an algorithm with runtime $T(n, n)$ where
$$
\begin{align*}
&T(x, c) = \Theta (x) &\ for\ c \le 2 \\
&T(x, y) = \Theta (x) + S(x, y/2) &\ \\
&S(c, y) = \Theta (y) &\ for\ c \le 2 \\
&S(x, y) = \Theta (y) + T(x/2, y) &\ \\
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

Rewriting the relation to avoid $\Theta$ notation, and expanding
$$
\begin{align*}
T(x, y) &= cx + \frac{cy}{2} + \frac{cx}{2} + \frac{cy}{4} +
            \frac{cx}{4} + \frac{cy}{8} + \frac{cx}{8} + ...\\
T(x, y) &= \{cx + \frac{cx}{2} + \frac{cx}{4} + \frac{cx}{8} + ...\} +
            \{\frac{cy}{2} + \frac{cy}{4} + \frac{cy}{8} + ...\}\\
&= 2cx\ +\ cy
\end{align*}
$$

#### Answer

$2. \Theta(n)$

# Peak Finding Problems

These problems are based on the following algorithms provided.

```python
def algorithm1(problem, trace = None):
    # if it's empty, we're done 
    if problem.numRow <= 0 or problem.numCol <= 0:
        return None

    # the recursive subproblem will involve half the number of columns
    mid = problem.numCol // 2

    # information about the two subproblems
    (subStartR, subNumR) = (0, problem.numRow)
    (subStartC1, subNumC1) = (0, mid)
    (subStartC2, subNumC2) = (mid + 1, problem.numCol - (mid + 1))

    subproblems = []
    subproblems.append((subStartR, subStartC1, subNumR, subNumC1))
    subproblems.append((subStartR, subStartC2, subNumR, subNumC2))

    # get a list of all locations in the dividing column
    divider = crossProduct(range(problem.numRow), [mid])

    # find the maximum in the dividing column
    bestLoc = problem.getMaximum(divider, trace)

    # see if the maximum value we found on the dividing line has a better
    # neighbor (which cannot be on the dividing line, because we know that
    # this location is the best on the dividing line)
    neighbor = problem.getBetterNeighbor(bestLoc, trace)

    # this is a peak, so return it
    if neighbor == bestLoc:
        if not trace is None: trace.foundPeak(bestLoc)
        return bestLoc
   
    # otherwise, figure out which subproblem contains the neighbor, and
    # recurse in that half
    sub = problem.getSubproblemContaining(subproblems, neighbor)
    if not trace is None: trace.setProblemDimensions(sub)
    result = algorithm1(sub, trace)
    return problem.getLocationInSelf(sub, result)

def algorithm2(problem, location = (0, 0), trace = None):
    # if it's empty, we're done 
    if problem.numRow <= 0 or problem.numCol <= 0:
        return None

    nextLocation = problem.getBetterNeighbor(location, trace)

    if nextLocation == location:
        # there is no better neighbor, so return this peak
        if not trace is None: trace.foundPeak(location)
        return location
    else:
        # there is a better neighbor, so move to the neighbor and recurse
        return algorithm2(problem, nextLocation, trace)

def algorithm3(problem, bestSeen = None, trace = None):
    # if it's empty, we're done 
    if problem.numRow <= 0 or problem.numCol <= 0:
        return None

    midRow = problem.numRow // 2
    midCol = problem.numCol // 2

    # first, get the list of all subproblems
    subproblems = []

    (subStartR1, subNumR1) = (0, midRow)
    (subStartR2, subNumR2) = (midRow + 1, problem.numRow - (midRow + 1))
    (subStartC1, subNumC1) = (0, midCol)
    (subStartC2, subNumC2) = (midCol + 1, problem.numCol - (midCol + 1))

    subproblems.append((subStartR1, subStartC1, subNumR1, subNumC1))
    subproblems.append((subStartR1, subStartC2, subNumR1, subNumC2))
    subproblems.append((subStartR2, subStartC1, subNumR2, subNumC1))
    subproblems.append((subStartR2, subStartC2, subNumR2, subNumC2))

    # find the best location on the cross (the middle row combined with the
    # middle column)
    cross = []

    cross.extend(crossProduct([midRow], range(problem.numCol)))
    cross.extend(crossProduct(range(problem.numRow), [midCol]))

    crossLoc = problem.getMaximum(cross, trace)
    neighbor = problem.getBetterNeighbor(crossLoc, trace)

    # update the best we've seen so far based on this new maximum
    if bestSeen is None or problem.get(neighbor) > problem.get(bestSeen):
        bestSeen = neighbor
        if not trace is None: trace.setBestSeen(bestSeen)

    # return if we can't see any better neighbors
    if neighbor == crossLoc:
        if not trace is None: trace.foundPeak(crossLoc)
        return crossLoc

    # figure out which subproblem contains the largest number we've seen so
    # far, and recurse
    sub = problem.getSubproblemContaining(subproblems, bestSeen)
    newBest = sub.getLocationInSelf(problem, bestSeen)
    if not trace is None: trace.setProblemDimensions(sub)
    result = algorithm3(sub, newBest, trace)
    return problem.getLocationInSelf(sub, result)

def algorithm4(problem, bestSeen = None, rowSplit = True, trace = None):
    # if it's empty, we're done 
    if problem.numRow <= 0 or problem.numCol <= 0:
        return None

    subproblems = []
    divider = []

    if rowSplit:
        # the recursive subproblem will involve half the number of rows
        mid = problem.numRow // 2

        # information about the two subproblems
        (subStartR1, subNumR1) = (0, mid)
        (subStartR2, subNumR2) = (mid + 1, problem.numRow - (mid + 1))
        (subStartC, subNumC) = (0, problem.numCol)

        subproblems.append((subStartR1, subStartC, subNumR1, subNumC))
        subproblems.append((subStartR2, subStartC, subNumR2, subNumC))

        # get a list of all locations in the dividing column
        divider = crossProduct([mid], range(problem.numCol))
    else:
        # the recursive subproblem will involve half the number of columns
        mid = problem.numCol // 2

        # information about the two subproblems
        (subStartR, subNumR) = (0, problem.numRow)
        (subStartC1, subNumC1) = (0, mid)
        (subStartC2, subNumC2) = (mid + 1, problem.numCol - (mid + 1))

        subproblems.append((subStartR, subStartC1, subNumR, subNumC1))
        subproblems.append((subStartR, subStartC2, subNumR, subNumC2))

        # get a list of all locations in the dividing column
        divider = crossProduct(range(problem.numRow), [mid])

    # find the maximum in the dividing row or column
    bestLoc = problem.getMaximum(divider, trace)
    neighbor = problem.getBetterNeighbor(bestLoc, trace)

    # update the best we've seen so far based on this new maximum
    if bestSeen is None or problem.get(neighbor) > problem.get(bestSeen):
        bestSeen = neighbor
        if not trace is None: trace.setBestSeen(bestSeen)

    # return when we know we've found a peak
    if neighbor == bestLoc and problem.get(bestLoc) >= problem.get(bestSeen):
        if not trace is None: trace.foundPeak(bestLoc)
        return bestLoc

    # figure out which subproblem contains the largest number we've seen so
    # far, and recurse, alternating between splitting on rows and splitting
    # on columns
    sub = problem.getSubproblemContaining(subproblems, bestSeen)
    newBest = sub.getLocationInSelf(problem, bestSeen)
    if not trace is None: trace.setProblemDimensions(sub)
    result = algorithm4(sub, newBest, not rowSplit, trace)
    return problem.getLocationInSelf(sub, result)
```
