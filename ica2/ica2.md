# For a given matrix size _N_, what is the total number of floating point operations performed by this operator?

`C_{ik} = A_{ij} * B_{jk}`

```
for i
  for k
    for j
      two floating operations
```

`2 * N^3`
