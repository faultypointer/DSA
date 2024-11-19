# Heap and Heap Sort

## Priority Queue

- set of elements, each elements associated with a key
- Operations
  - Insert (S, x): insert x into set S
  - max(S): return element from S with largest key
  - extraxt_max(S): remove and return element from S with largest key
  - increase_key(S, x, k): increase key of x element from set S to value k
  
## Heap

- array visualized as nearly complete binary tree
- each node corresponding to an array

```example
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
arr as heap is represented as
root: 1
    l: 2
        l: 4
            l: 8
            r: 9
        r: 5
    r: 3
        l: 6
        r: 7
```

### Heap as a tree

- root of tree is first element of array (i=1)
- parent(i) = i/2
- left(i) = 2i
- right(i) = 2i + 1

### Max Heap

- The key of a node is $\ge$ to the key of its children
- get max element in $\mathcal{O}(1)$

### Heap Operations (for max heap)

- build_max_heap: produce max heap from unordered array
- max_heapify: correct single violation of max heap property in a subtree's root

#### Max Heapify (A, i)

- assume trees rooted at left(i) and right(i) are max heaps
- time complexity: $\mathcal{O}(\log n)$

```pseudocode
Max-Heapify(A, i)
    l = left(i)
    r = right(i)
    if l <= A.heap-size and A[l] > A[i]
        largest = l
    else largest = i
    ir r <= A.heap-size and A[r] > A[largest]
        largest = r
    if largest != i
        exchange A[i] with A[largest]
        Max-Heapify(A, largest)
```

#### Build Max Heap (A)

- converts A[i..n] to a max heap
- time complexity:
  - upper bound: $\mathcal{O}(n \log n)$ (is correct but)
  - tight bound: $\Theta(n)$

```pseudocode
Build-Max-Heap(A)
    for i = n/2 down to 1
        Max-Heapify(A, i)
```

## Heap Sort

```pseudocode
Heap-Sort(A)
    Build-Max-Heap(A)
    for i = A.length downto 2
        exchange A[1] with A[i]
        A.heap-size = A.heap-size - 1
        Max-Heapify(A, 1)

```
