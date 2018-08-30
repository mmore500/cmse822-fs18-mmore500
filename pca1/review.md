# key points from the reading

## 1.1 Von Neumann architecture

key idea: program instructions are treated just like other data (kept in the same storage)

instruction flow:
* instruction fetch/decode
* memory fetch
* execute operation on data in registers
* write-back to memory

modern complications:
*  memory locality
*  instruction level parallelism

## 1.2 Modern processors
* out-of-order processing, so long as result stays intact
* lots of hardware optimizations for floating point operations
  * except for floating point divide
* pipelining
  * it's like commercial laundromats where laundry goes through the washer then, while that laundry is drying, new laundry goes through the washer
  * works when pipeline inputs don't depend on outputs currently in the pipeline
  * limited speedup, already tapped
* more detail on instruction level parallelism
  * run independent instructions at the same time
  * pipelining
  * branch prediction/speculative execution (try with assumption, trash results if assumption wrong)
  * out-of-order execution: like tetris; rearrange instructions for efficiency
  * prefetching: try to predict data and grab it into cache before needed

## 1.3 Memory Hierarchy

low capacity, fast access
* registers (on chip)
* L1 (SRAM)
* L2 (SRAM)
* L3 (if available) (SRAM)
* memory (DRAM)
* disk
large capacity, slow access

how to decide what to kick out of cache?
* least recently used
* first in first out
* random

bus: wiring between levels
* bandwidth generally less than maximum CPU throughput
* need re-use of data for efficiency

data is stored in caches in pages
* do sequential access of data where possible in order to maximize your use of what's already in the cache
* sequential access is also good for maximizing bandwidth use with interleaved memory banks (section 1.3.7)

cache mapping: how you keep track of what's in your cache
* direct map: use least selective binary digits of memory address to determine data position in the cache
  * efficient
  * can have collisions even if cache isn't full
* associative map: ideally, want data to go in any cache location so that only conflict is cache filling up
  * costly to build, much slower than direct-mapped cache
  * compromise: k-way associative cache where any item can go into any available among k possible spots
  * k+1 way conflict required before data dumping from cache before it's full

concurrency: amount of data "in flight" at a single time

throughput: amount of data transferred per unit time

`concurrency = bandwidth * latency`

`effective throughput = achieved concurrency / latency`

virtual memory
* when memory full, swap some memory out to disk
* sometimes efficient to use large page size
  * minimize number of swaps by using all the localized memory in a single page
  * however, if you don't use localized memory swapping big pages onto and off the disk can be wasteful
* use translation look-aside buffer (TLB) as a very fast to keep track of commonly used pages
  * provides memory address translation
  * usually associative with least recently used policy

# questions

Some of the notation in the reading isn't introduced well.
In particular, I'm left wondering what `n_{1/2}` represents (pg 17).
I am also left unclear as to the exact meanings of `T_s(n)` and `T_0(n)` in exercise 1.4.

Also, I am curious if the "register" directive is valid in C++ in addition to C.
Is it ever used in practice?
