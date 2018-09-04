# key points from the reading

## 1.4 Multicore Architectures

core:
own private L1 cache

socket:
cores sharing L2 cache

node:
sockets sharing memory controller for a subset of memory

### cache coherence

problem:
one processor might have an out-of-date cached version of memory (i.e., was modified by another processor)

solution:
update or invalidate cachelines as an atomic memory store operation
* taken care of on the very low level of the processor
* option 1: "snooping" (listen in to bus traffic to know what all cores using; doesn't scale well)
* option 2: "directory-based scheme" (use tag directory, central location with what info is present in what cache)
* invalidating is cheaper than updating

scratch:
the cache line does not contain a copy of the item

valid:
the cache line is a correct copy of data in main memory

reserved:
cache line is only copy of a piece of data

dirty:
the cache line has been modified, but not yet written back to main memory

invalid:
data on cache line is also present on other processors (not reserved) and another process has modified its copy of the data

(there is a simpler variant of this scheme called Modified-Shared-Invalid)

## etc

* two options for parallelism: MPI and OpenMP

* processors also need to synchronize translation lookaside buffer (TLB)

## 1.5 Node Architecture and Sockets

* Non-Uniform Memory Access (NUMA): each socket has attached memory
  * make sure that memory contents are kept next to socket using them

## 1.6 Locality and Data Re-Use

arithmetic intensity
* `n` number of data items
* `f(n)` number of operations
* arithmetic intensity: `f(n)/n`
* latency hiding: are you doing enough operations that memory lag isn't the limiting factor

roofline model
* memory-bound (slanty bit) vs CPU-bound (peak performance)

locality:
* temporal: use of a data element within a short time of its last use (exploit cache LRU policy)
* spatial: references memory that is 'close' to memory it already referenced
  * e.g., exploit cachelines
* core: write accesses that are spatially or temporally close are performed on the same core/processing unit
  * limit performance wasted managing cache coherence

## 1.7 Programming Strategies for High Performance

peak performance:
* Linpack benchmark

pipelining:
* loop unrolling to make intermediate operations (between loop steps) independent
* register spill: when we want to use more registers than there actually are
* cache size: try to schedule re-use before the data gets kicked out of the cache
* cache lines: try to keep strides small
* TLB: try to schedule data re-use befoe cached info gets kicked out
* cache associativity:
  * many artchitectural features of CPUs are built around powers of two, soi algorithms operating on vectors of length of powers of two can run into problems
  * try to avoid accessing sequences of data that map to the same cache location
* loop nests: if iteration independent, get to choose how to nest
  * programming in C with 2d array indices `(i,j)`, often let `j` be inner index
  * parallelism: often want short inner loop (unless targeting a GPU, a large inner loop is great)
* loop tiling: breaking a loop into two nested loops
  * cache blocking, divide array into blocks that will fit in the cache

optimization strategies:
* cache aware
  * try to chunk out so that data is re-used while still in the cache
  * dependent on particular hardware, not necessarily portable
* cache oblivious
  * try to automatically use all levels of cache hierarchy using a divide-and-conquer (recursive) strategy

## 1.8 Further topics

while miniaturizing hardware by a factor of `s`

* feature size `~ s`
* voltage `~ s`
* current `~ s`
* frequency `~ s`
* power `= V * I ~ s^2`
* charge `q = CV`
* work `W = qV = cV^2`
* power = `W/time = W F = CV^2F`

multicore: two half as fast processors
* `C_{multi} = 2C`
* `F_{multi} = F/2`
* `V_{multi} = V/2`
* so
* `P_{multi} = P/4`
* not actually quite this good

operating system:
can make it interrupt less often
* avoid overhead and jitter
* less cache and TLB pollution

# questions

Typo on page 59, "matrix!matrix product!tiling"?

Do any of the libraries that are commonly used to do linear algebra (i.e., matlab, numpy, etc.) take advantage of autotuning?
Is this something you have to turn on manually?
Or are the autotuning projects described more like libraries to use directly in your own codebase?
Would autotuning need to take place every time that a program is run on a particular machine, or can it be completed once and then the results stored somewhere on the system and automatically re-used?

Is information about system specifics (cache size, etc.) at all available as macro constants (or somehow else} in C?
