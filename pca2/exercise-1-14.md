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