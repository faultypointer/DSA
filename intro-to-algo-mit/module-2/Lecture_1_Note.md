# Insertion Sort and Merge Sort

## Insertion Sort

for i = 1 to n
    insert A[i] into sorted array A[1..i-1] by pairwise swaps down to correct position

time: $\mathcal{O}(n^2)$

## Merge Sort

- divide and conquer
- recursively split array A into 2 subarrays L, R
- merge the partitioned array into a sorted array at each level

### Complexity

$$
T(n) = \underbrace{C_1}_{divide} + \underbrace{2T(n/2)}_{recursion} + \underbrace{Cn}_{merge}\\
$$
