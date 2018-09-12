# For a given matrix size _N_, what is the total number of floating point operations performed by this operator?

`C_{ik} = A_{ij} * B_{jk}`

```
for i
  for k
    for j
      two floating operations
```

`2 * N^3`

# For the system you are running on, determine the clock speed of the processor and the cache size/layout.
Assuming that the processor is capable of one flop per clock cycle, how does the performance you measures in (3) compare to the theoretical peak performance of your system?

We ran the code on `Intel(R) Core(TM) i7-7500U CPU @ 2.70GHz`.

Without `-O3`, we used at most only about a fifth (20%) of peak performance (~0.5 GFlops) for N < 100.
With `-O3`, we saw close to 2.1 GFlops for N < 100, about 77% of peak performance.

# How does the measured performance for multiple _N_'s compare to peak?
Are there any "features" in your plot? Explain them in the context of the hardware architecture of your system.
Include in your write-up a description of your system's architecture (processor, cache, etc.).

The same general features are observed with and without `-O3`.

For very small `N` (< 50), performance is relatively poor.
Perhaps this is because there is little absolute data re-use (a very small amount of data is pulled up in the first place) so most programmatic time is spent fetching data from memory, not actually performing matrix mutliplication computations.

For slightly larger `N` (< 100), performance peaks.
Next, performance dips and plateaus until N around 400 or 500, then dips sharply.
The rate of performance decrease flattens slightly as N passes 1000 and then dips sharply once more.

The sharp dips between plateaus might correspond to data filling L1 and then getting bumped to L2, filling L2 and then getting bumped to L3.

We grabbed the following data about our CPU's cache size from [http://www.cpu-world.com/CPUs/Core_i7/Intel-Core%20i7%20i7-7500U.html](http://www.cpu-world.com/CPUs/Core_i7/Intel-Core%20i7%20i7-7500U.html).

| cache | memory     |
|-------|------------|
| L1    | 2 x 32 KB  |
| L2    | 2 x 256 KB |
| L3    | 4 MB       |

Here's a little bit of scratch work roughly figuring the matrix size that would fit completely in cache for different cache sizes.
We're not sure how `2 x` figures in, so we calculated two possible `N`'s for L1 and L2.

```
a double is 8 bytes

 L1
----
32 KB ~ 4k bytes -> N ~ 63
64 KB ~ 8k bytes -> N ~ 89

L2
----
256 KB ~ 32k bytes -> N ~ 178
512 KB ~ 64k bytes -> N ~ 252

L3
----
4MB KB ~  500k bytes -> N ~ 707
```

Note that this is assuming only a single matrix in memory.
We're actually multiplying two matrices, but this gets us in the ballpark.

These N values roughly correspond to the points at which we saw performance decreases, suggesting that we might be observing cache effect sizes.

The N values don't exactly match up with the rough calculations (we observe apparent cache-filling at slightly larger N than expected ), this might perhaps be perhaps because we found incomplete, old, or erroneous specifications for the processor or because we didn't interpret the specifications completely correctly (particularly because it's a four-core chip).
