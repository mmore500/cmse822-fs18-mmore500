# key points

## affinity

`OMP_PROC_BIND`
* `close` or `spread` or `master`
* or `true` (lock threads to a core; safe default)
* `false` set no binding

`OMP_PLACES`
* `sockets` or `cores` or `threads` (e.g., hypertheads)

useful for debugging: `OMP_DISPLAY_ENV`

performance
* avoid threads inadvertently ending up on the same core
  * for compute-bound processes using `OMP_PLACES=cores` is good
* spreading over sockets is good to make use of bandwidth for memory-bound applications

spreading over sockets is good for

custom definitions possible

first-touch
* memory is *actually* allocated the first time it's written to
* if you're not careful, you can have all the memory associated with the master thread's socket (which is slow to read/write from other sockets)

## memory model

updating a variable locally doesn't necessarily mean that it will be updated in memory (might just stay in the registers for a while) [?]
* need to flush [?]

race conditions: when two threads access the same data item

rule about multiple-thread access of a single data item:
Any memory location that is written by one thread can not be read by another thread in the same parallel region, if no synchronization is done.

flushing
* there is an implicit flush of all variables at the start and end of a parallel region
* there is a flush at each barrier (explicit or implicit)
  * e.g., at the end of a work sharing construct
* at entry and exit of a critical section
* when a lock is set or unset

# questions for class

What do the curly braces mean in the `OMP_PLACES` custom syntax?

What is the use case for the `OMP_PLACES` custom syntax

When would you want to use system-level affinity control?
