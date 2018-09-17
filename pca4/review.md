# review

thread (OpenMP)
* each thread has own stack
* shares heap, program code

data race: when result depends on ordering that threads using same memory run their operations

critical sections:
* semaphore on code (can unnecessary block other threads that are accessing different memory)
* lock on memory (thru operating system, which is slow)

affinity: mapping between threads or processes and cores
* want to avoid switching between cores due to overhead
* close affinity: minimize communication delays between threads/procs
* spread affinity: maximize available bandwidth to threads/procs (each has its own socket)

message passing: MPI
* avoid deadlock/serial message passing
  * e.g. have even procs send, odds receive then vice versa

blocking vs non-blocking communication
* blocking: send and wait for message to be received
* non-blocking: do some work while waiting for confirmation of send then wait for everyone to catch up with a blocking fence; have to manage available message buffers

OpenMP: start with serial, incrementally add parallelization
MPI program: all-or-nothing

MPI routines
* process management
* point-to-point communication
* collective calls
  * reduction
  * gather
  * broadcast
  * scatter
  * all-to-all

one-sided communication
  * write into neighbor's memory in specified window
  * often used with blocking fence

hybrid strategy:
MPI processes with OpenMP inside
* OpenMP threading is more flexible (OS overhead, though)
* bundles messages: two MPI processes send messages to each of two processes on another node = four mesasge, but in hybrid model bundled into one message

active messages (charm++):
* message passes calls a function that handles the message in the receiver
* this is basically event-driven computation

bulk synchronous parallelism:
* programmer spells out communications, but not their ordering
* supersteps, each of which ends with a barrier sync
* one-sided communication
* overdecomposition
* random placement of data and tasks to avoid load inbalance

data dependencies
* flow ('read-after-write')
* anti ('write-after-read')
* output ('write-after-write')

# questions

A new question from material a few sections ago:
when calculating arithmetic intensity, why don't we take into account the behind-the-scenes arithmetic that's required to index into arrays (i.e., multiplying the index by the stride, adding the displacement to the pointer to the beginning of the array).
Is this because these are integer operations, which are much faster than floating point operations?
Or are these just written off as a part of memory access?

I don't understand the examples in the section "Affinity and data access patterns" (p 102).
Why is the code broken up over even/odd indices on the second code snippet?
Is this code snippet representing a problematic situation or the solution to a problem?
