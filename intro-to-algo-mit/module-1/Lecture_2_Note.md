# Model of Computation, Document Distance

## Whats an Algorithm?

computational procedure for solving a certain problem
input -> algorithm -> output

## Model of Computation

specifies

- what operations an algorithm is allowed
- cost (time, space, ...) of each operations

### Random Access Machine

- modelled by big array
- has $\mathcal{O}(1)$ register
- in $\mathcal{O}(1)$ time algorithm can
  - load $\mathcal{O}(1)$ words
  - do $\mathcal{O}(1)$ computations
  - store $\mathcal{O}(1)$ words
  
### Pointer Machine

- dynamically allocated objects
- object as $\mathcal{O}(1)$ fields
- field = word or pointer
- pointer = points to objects or null

## Document Distance

- applications: find similar documents, detect duplicates and plagiarims, web search
- d(D1, D2)
- document = sequence of words
- word = string of alphanumeric characters
- idea
  - shared words
  - document as vector
  - D[w] = no. of times w occurs in D

### Algorithm

1. split doc into words
2. compute word frequencies (document vector)
3. dot product (and divide)
