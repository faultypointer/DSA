# Binary Search Tree, BST Sort

## Runway Reservation System

- Airport with single Runway
- Reservations for future landings
  - Reserve request specifies landing time t
  - add t to set R if no other landings are scheduled within k minutes
- remove from set R after plane lands
- constraints:
  - $|R| = n$
  - $\mathcal{O}(\log n)$

## Binary Search Tree

- rooted binary tree
- each node has
  - key
  - left pointer
  - right pointer
  - parent pointer
- BST property
  - left child has key less than or equal to that of current node's key
  - right child has key greater than or equal to that of current node's key
- Operations:
  - find-min: go to left till leaf; $\mathcal{O}(h)$
  - next-larger(x): $\mathcal{O}(h)$
  
### Augment the BST Structure

- store extra information in each nodes of tree aside from key and pointers
- update those extra info with each insert and delete
