# 1
Report your timings for the host, naive CUDA kernel, shared memory CUDA kernel,
and the excessive memory copying case, using block dimensions of 256, 512,
and 1024. Use a grid size of `2^15+2*NG` (or larger) and run for 100 steps (or
shorter, if it's taking too long). Remember to use `-O3`!

## Response

| algorithm     | msec/step @ block dim 256 | msec/step @ block dim 512 | msec/step @ block dim 1024 |
|---------------|---------------------------|---------------------------|----------------------------|
| host          | 23.2258ms                 | 23.4288ms                 | 25.1603ms                  |
| cuda          | 22.8433ms                 | 23.057ms                  | 24.4994ms                  |
| shared mem    | 22.8936ms                 | 23.0831ms                 | 24.6877ms                  |
| excessive cpy | 232.394ms                 | 232.615ms                 | 244.734ms                  |

# 2
How do the GPU implementations compare to the single threaded host code. Is it
faster than the theoretical performance of the host if we used all the cores on
the CPU?

## Response

The GPU implementations are slightly faster than the host code, but not by much.
The speedup might be masked by overhead, like spending a significant proportion of runtime on I/O operations (e.g., writing the results out to file).
Perhaps running on a larger problem size would yield a more noticeable speedup due to the larger ratio of the parallelizable work to the overhead that cannot be parallelized.

The speedup is not faster than the theoretical performance of the host if we used all the cores on the CPU... it's not even twice as fast!

# 3
For the naive kernel, the shared memory kernel, and the excessive memcpy case,
which is the slowest? Why? How might you design a larger code to avoid this slow down?

## Response

By far, the excessive memcpy case is the slowest!
It is about 10x as slow as the other approaches.
This really goes to highlight the cost of transferring data between the host and the device.
If you were to "design a larger code," you would want to minimize transfers between the host and the device.
You might make data transfers only one way (e.g., the device reporting to the host) or accumulate results on the device and then report them all back to the host at the end of the run.

# 4
Do you see a slow down when you increase the block dimension? Why? Consider
that multiple blocks may run on a single multiprocessor simultaneously, sharing
the same shared memory.

## Response

I did observe a slight slowdown at a larger block dimension of 1024.
This difference was slight, but maybe like I said in Part 2, the problem here is that the performance of the parallelizable parts of the code are being masked by non-parallelizable overhead.

If blocks are larger, the same number of blocks will have a larger memory footprint.
Therefore, if the same number of blocks are scheduled on a single multiprocessor, but the blocks are larger, more shared memory might be consumed.
At a certain point, the memory might have to fall back to a slower cache level because the single multiprocessor's shared memory fills.
We might expect such a slow-down for larger blocks to be especially apparent in the shared memory approaches, where we are explicitly allocating dynamic shared memory for each block, but the data doesn't obviously bear this prediction out... the slowdown appears in all the CUDA algorithms, no matter whether they allocate shared memory or not.
