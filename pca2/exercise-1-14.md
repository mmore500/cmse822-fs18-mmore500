# prompt

Consider the following pseudocode of an algorithm for summing `n` numbers `x[i]` where `n` is a power of 2:

```
for s=2,4,8,...,n/2,n:
  for i=0 to n-1 with steps s:
    x[i] = x[i] + x[i+s/2]

sum = x[0]
```

Analyze the spatial and temporal locality of this algorithm, and contrast it with the standard algorithm:

```
sum = 0
for i=0,1,2,...,n-1:
  sum = sum + x[i]
```

# response

In the standard algorithm, each addition uses the result of the previous addition as an operand, so pipelining isn't possible.

In the top algorithm, the result of each addition isn't immediately used in the next addition so pipelining can be exploited.

Thus, we should expect a speed up by a constant factor that depends on the performance of the pipeline.

However, the top algorithm has `O(n * log n)` additions while the standard algorithm has `O(n)` additions.
Thus, at the limit of `n` the standard algorithm will perform better.
However, for small (or medium) `n` the top algorithm may perform better, depending on the efficacy of pipelining.