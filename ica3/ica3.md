# In-class problem

Compute the arithmetic intensities of the following kernels assuming 8 bytes per float.

```C
  Y[j] += Y[j] + A[j][i] * B[i]
```

loads:
* `Y[j]`
* `A[j][i]`
* `B[i]`

stores:
* `Y[j]`

operations:
* `+`
* `+`
* `*`

```
f(n) = 3 operations
n = 4 * 8 bytes

arithmetic intensity
  = f(n) / n
  = 3 operations / 24 bytes
  = 0.125 operations / byte
```

```C
  s += A[i] * A[i]
```

loads:
* `A[i]`

operations:
* `*`
* `+`

```
f(n) = 2 operations
n = 1 * 8 bytes

arithmetic intensity
  = f(n) / n
  = 2 operations / 8 bytes
  = 0.5 operations / byte
```

```C
  s += A[i] * B[i]
```

loads:
* `A[i]`
* `B[i]`

operations:
* `+`
* `*`

```
f(n) = 2 operations
n = 2 * 8 bytes

arithmetic intensity
  = f(n) / n
  = 2 operations / 16 bytes
  = 0.125 operations / byte
```

```C
  Y[i] = A[i] + C*B[i]
```
loads:
* `A[i]`
* `B[i]`

stores:
* `Y[i]`

operations:
* `+`
* `*`

```
f(n) = 2 operations
n = 3 * 8 bytes

arithmetic intensity
  = f(n) / n
  = 2 operations / 24 bytes
  = 0.083 operations / byte
```

# Roofline exercise

3. Run the ERT in serial mode on your local machine. Report the peak performances and bandwidths (for all caches levels as well as DRAM). Where is the "ridge point" of the roofline for the various cases?

My peak performance is 32.2 GFLOPs/sec.

My bandwidths are:
* L1 136.5 GB/s
* L2 66.6 GB/s
* L3 51.0 GB/s
* L4 24.6 GB/s
* DRAM  15.6 GB/s

The ridgepoints of the roofline occur at:
* L1 0.22 Flops/Byte
* L2 0.47 Flops/Byte
* L3 0.61 Flops/Byte
* L4 1.2 Flops/Byte
* DRAM 1.1 Flops/Byte

4. Consider the four FP kernels in "Roofline: An Insightful Visual Performance Model for Floating-Point Programs and Multicore Architectures" (see their Table 2). Assuming the high end of operational (i.e., "arithmetic") intensity, how would these kernels perform on your local machine? What optimization strategy would you recommend to increase performance of these kernels?

| kernel                                 | operational intensity |
|----------------------------------------|-----------------------|
| Sparse Matrix-Vector Multiplication    | 0.25 Flops per byte   |
| Lattice-Boltzmann Magnetohydrodynamics | 1.07 Flops per byte   |
| Stencil                                | 0.33 Flops per byte   |
| 3-D Fast Fourier Transform             | 1.64 Flops per byte   |


The 3-D Fast Fourier transform lands squarely in the "roof" section of my roofline plot.
The performance of this kernel might be improved by purchasing a faster CPU or overclocking the existing CPU.

Lattice-Boltzmann Magnetohydrodynamics falls onto the "roof" section of my roofline plot if use of DRAM is avoided (i.e., problem size fits in L4 cache).
Perhaps applying blocking to iterated loops (in order to more efficiently use data in cache) or splitting up work over multiple cores (in order to reduce the total amount of data per core) could help us achieve peak performance.

The Stencil and Sparse Matrix-Vector Multiplication kernels land on the "roof" section of the plot only if the L1 cache is exclusively used.
As for the L-B M kernel, blocking iterated loops and splitting work over multiple cores may help us improve performance, but almost certainly won't get us to peak performance.
These kernels are very memory-bound.
We might be able to improve our computational performance by using hardware with larger DRAM bandwidth (perhaps saving money by purchasing a CPU with lower peak performance because we won't be able to take advantage of it for these applications.
