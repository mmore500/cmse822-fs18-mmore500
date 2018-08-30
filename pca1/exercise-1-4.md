# prompt

The operation

```
for (i) {
  x[i+1] = a[i] * x[i] + b[i];
}
```

can not be handled by a pipeline because there is a *dependency* between input of one iteration of the operation and the output of the previous.
However, you can transform the loop into one that is mathematically equivalent, and potentially more efficient to compute.
Derive an expression that computes `x[i+2]` from `x[i]` without involving storage.
You can perform the calculations by:
* doing some preliminary calculations;
* computing `x[i]`, `x[i+2]`, `x[i+4]`, ..., and from these,
* compute the missing terms `x[i+1]`, `x[i+3]`, ...

Analyze the efficiency of this scheme by giving formulas for `T_0(n)` and `T_s(n)`.
Can you think of an argument why the preliminary calculations may be of lesser importance in some circumstances?

# response

Derivation of an expression to compute `x_{i+2}` from `x_i`.
```
x_{i+1} = a_i * x_i + b_i

x_{i+2} = a_{i+1} * x_{i+1} + b_{i+1}

x_{i+2} = a_{i+1} * (a_i * x_i + b_i) + b_{i+1}
x_{i+2} = a_{i+1} * a_i * x_i + a_{i+1} * b_i + b_i * b_{i+1}
```

Computing `x[i]`, `x[i+2]`, `x[i+4]`, ...

```
for (i = 0; i += 2; i < N) {
  x[i+2] = a[i+1] * a[i] * x[i] + a[i+1] * b[i] + b[i] * b[i+1];
}
```

If you wanted to, you could calculate out arrays `z` and `y` ahead of time like so:

```
for (i) {
  z[i] =  a[i+1] * a[i];
  y[i] = a[i+1] * b[i] + b[i] * b[i+1];
}
```

in order to simplify the computation of the even-indexed elements of `x`

```
for (i = 0; i += 2; i < N) {
  x[i+2] = z[i] * x[i] + y[i];
}
```

The odd-indexed elements of `x` would then be calculated as

```
for (i = 0; i += 2; i < N) {
  x[i+1] = a[i] * x[i] + b[i];
}
```


# analysis of efficiency

I assume that `T_s(n)` represents how long it takes to perform setup (i.e., fill in vectors (`y` and `z`).
We're only filling in half of each vector (every other spot).
However, the calculations independent so they can be pipelined.
Thus, we're looking at time complexity along the lines of
```
2 * [n/2 + l - 1] * \tau
```
where `l` is pipeline length and `tau` is clock cycle time, assuming setup cost `s` is zero.


I assume that `T_0(n)` represents the time to calculate elements of `x` following setup.
First, we need to calculate the `n/2` even-indexed elements of `x`, which can't be pipelined because the calculations are dependent.
```
n/2 * l * \tau
```
Next, we need to calculate the `n/2` odd-indexed elements of `x`, which can be pipelined because the calculations are independent.
```
[n/2 + l - 1] * \tau
```

Thus, we arrive at `T_0(n)`,
```
[n/2 * (l + 1) + l - 1] * \tau

```

# importance of preliminary calculations

Preliminary calculations aren't as expensive as they might seem at first blush because they can be pipelined as they are independent of each other.
For large `n`, pipelining can approach a speedup multiplier of the number of stages of the pipeline.
Thus, they might be able to be completed in a fraction of the time required to complete the other non-independent calculations (i.e., calculating the odd' indexed elements of `x`).
If you/the hardware folks are sufficiently clever, perhaps you could even run some of the preliminary calculations through the pipeline during otherwise wasted "bubbles" in the pipeline introduced by dependent calculations that need to wait on the previous calculation to exit the pipeline.
