# Review

kernels --- executed N times in parallel by N different CUDA threads
* use `__global__` to declare
* you can access `threadIdx`, `blockIdx`, `blockDim` variables within kernel

* threads
* can be grouped together in 1d, 2d, or 3d arrangements (up to 1024 of them) to make
* blocks
* can be grouped together in 1d, 2d, or 3d arrangements to make
* grids

threads within a block can synchronize, but synchronization between grids isn't supported
* blocks represent interchangeable, rearrangeable, work

memory is local to threads, can be shared within a block, and everyone (across different blocks) can access global memory
* you are in charge of managing/syncing memory between device (GPU) and host (CPU)

CUDA C program outline:
0. start
1. declare and allocate host and device memory
2. initialize host data
3. transfer data from the host to the device
4. execute one or more kernels
5. transfer results from the device to the host
6. done

use `nvcc` to compile

you can use static or dynamic memory within kernels
* in order to have multiple dynamic arrays or dynamic arrays of different type,you have to do all the bookkeeping yourself on a single dynamic array

avoid memory access collisions into the same memory bank
* that way, each bank can be drawn from simultaneously, increasing effective bandwidth

exploit memory locality by breaking up matrix transpose so that you access contiguous/nearby chunks of memory

# Your Questions

1. List the CUDA _thread_ hierarchy from smallest to largest.

*smallest*
1. thread
2. block
3. grid
*largest*

2. List the CUDA _memory_ hierarchy from smallest to largest.

*smallest*
1. per-thread local memory
2. per-block local memory
3. global memory
*largest*

# My Questions

Is this thread-block-grid decomposition universal among interfaces to program GPUs?
Or do other GPU programming interfaces (e.g., OpenCL) provide fundamentally different paradigms?

Are there widespread alternatives to CUDA?
What applications is CUDA used for versus alternatives.

What is a "warp"?

What is "memory coalescing"?
