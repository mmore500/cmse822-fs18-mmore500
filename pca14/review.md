# key points

## Getting Started with OpenMP

* MPI is great to communicate between cluster nodes
* but there's multiple cores all sharing memory within a node!
  * a node has up to four sockets
  * a socket has up to 24 cores
* also, fork/join model
  * MPI: external forces control number of procs
  * OpenMP: number of threads can change dynamically

* in C++, use `pragma` directives
* parallel regions are defined by scope (i.e., `{ ... }`)

*structured block* single statement, a compound statement, or a block in braces
* cannot be jumped into or contain a jump statement leaving it

*construct* the section of code starting with a directive and spanning the following structured block
  * a lexical concept: contains statements directly enclosed, but not any subroutines called from them

## Parallel regions

`#pragma omp parallel`
* code is executed by a newly created team of threads
* single program, multiple data model
  * use function `omp_get_thread_num` to figure out what thread you are and execute your work
  * master thread is the thread that was already active, will remain active already

nested parallelism is turned off by default, but it is an option
  * i.e., threads forking further threads

`#pragma omp for`
* parallelizes loop over existing threads from `#pragma omp parallel`

## Loop parallelism

options to schedule a for loop
* dynamic vs static
  * dynamic: iterations are assigned to unoccupied threads
  * dynamic is good if iterations take unpredictable time, but has overhead
* for static, you can set the chunk size
  * smaller chunks is good for load balancing, but has overhead
* guided: chunks get smaller further on in the Loop

* also, can leave it up to runtime
  * auto (implementation's choice)
  * runtime (set using `OMP_SCHEDULE` environment variable)

fancy footwork:
  * reductions
  * collapsing nested loops
  * ordered iterations (like locking a critical region)
  * nowait (let any thread immediately take on next work when done with for loop)

# questions for class

What's the difference between a structured block and a construct?
Is this actually important to know in practice?

How exactly would the work in the nested for loop on page 231 be scheduled between existing threads?
