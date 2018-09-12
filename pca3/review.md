# review

We can represent parallel computations using graphs where nodes are tasks and connections are dependencies.

Functional parallelism vs data parallelism
* data parallelism: single instructions in flight at the same time
* task parallelism: aka functional parallelism, separate subprograms in flight at the same time

* `T_1`: runtime w/o parallelism
* `T_p`: runtime with p processor parallelism
* speedup `S_p`: `T_1/T_p`
* efficiency `E_p`: what proportion of maximum speedup achieved? i.e., `S_p/p`
  * `0 < E_p < 1.0`
* overhead `T_o`: `p * T_p - T_1`
  * difference between simulating parallel algorithm on single processor and actual best sequential algorithm
  * cost-optimal if overhead is at most of the order of the running time of the sequential algorithm

due to physical constraints, speedup is limited to `n^{1/4}` for a problem on `n` processors, no matter the interconnect

Amdahl's law: parts of a code are inherently sequential, so increasing numbers of processors will eventually be unable to increase performance
* `F_s` sequential fraction
* `F_p` parallelizable fraction
* `T_p = T_1(F_s + F_p/p)`
* `S_p \leq 1 / F_s`, `E ~ 1/P`
* `T_p = T_1(F_s + F_p/p) + T_c` with communication overhead
  * if `F_p = 1`, `S_p = \frac{T_1}{T_1/p + T_c}`
  * to get speedup to be something similar to `p`, we need `T_c << T_1/p` aka `p << T_1/T_c`

Gustafson's law:
* more realistic assumption: there is a sequential fraction independent of the problem size and parallel fraction that can be arbitrarily replicated
* `T_p = F_s + F_p = 1`
* `T_1 = F_s + p * F_p`
* `S_p = F_s + p * F_p`
  * `= F_s + p * (1 - F_s)`
  * `= p - p * F_s + F_s`

strong scalability
* if partitioned over more and more processors, we get perfect or near perfect speedup
* `E_p ~ constant` as `p -> \infty` but `N` constant

weak scalability
* as problem size and number of processors grow in such a way that the amount of data per processor stays constant, the execution time also stays constant
* `E_p ~ constant` as `p -> \infty` and `N -> \infty`

scalable computer: no bottleneck

simulation scaling
* specific results for time-dependent PDEs and matrix-matrix products

* sequential computation rate `R_1(n)`: `n/T_1(n)`
* sequential computation rate `R_p(n)`: `n/T_p(n)`
* `S_p(n) = R_p(n) / R_1(n)`

concurrency: tasks that are simultaneously active with no temporal ordering between their actions

* SISD: traditional CPU
* SIMD: vector/GPU
* MIMD: most parallel computers

uniform memory access: everybody uses same memory, but maintaining cache coherency is difficult
* easier to conceptualize
* multicore computers

non-uniform memory access (NUMA):
* spatial position of processor determines route to memory, local memory it can access

logically vs physically distributed memory
* how are things connected?
* does each processor have its own separate memory space?

* data-level parallelism
* instruction-level parallelism
* task-level parallelism
  * master-slave
  * self-assigned (branching)

# questions

I don't understand what hybrid programming is section 2.2.3.3 or what the point the section is trying to make.

I don't understand the algebra on the top of page 79.
Is there a mistake?

Is strong scalability even possible??
Eventually you will hit number of processors = number of instructions in sequential version and you'll be done.
