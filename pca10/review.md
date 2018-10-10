# review

remote memory access:
you don't have to pair send and receive calls, you just put content directly into another processes' memory or take content directly from another processes' memory.

active RMA: target sets boundaries on the time period during which its window can be accessed

passive RMA: no limitation on when the window can be accessed
* trickier than it sounds: need a daemon on target or can lead to strange deadlocks

epochs (time periods for getting from or putting to a window) are defined by window fences

accumulate: performs a reduction operation on the results that are being put
* "a reduction with remote result"

request-based one-sided operations exist

assertions: describe activity before, during, and after an epoch
* combine them with bitwise OR

atomic operations
* avoid race conditions
* also available: locking/unlocking a window (but this can be slow)

window memory can be user-allocated or MPI-allocated

implementation: the fence calls are where the communication operations are actually performed

# your questions

1. What is a "window" in the context of one-sided MPI communication?

A window is a chunk of memory in each process in a collective that is "exposed" to other processes.
Depending on subsequent operations, the window can be read out of or written into by other processes.
This operation is one-sided because, in the code you write, the window-bearing process does not need to acknowledge the operations by other processes on its window.

2. In a given `epoch`, how many processes can execute a `put` in the same `window`?

On page 157, it states that only one process can perform a `put` on a certain window within an epoch.
This makes sense because if more than one process were able to perform a `put`, we could have race conditions.

# my questions

I don't exactly understand the role of asserts with respect to defining epochs for windows.
Do asserts alter the behavior of the code in a particular epoch, or they just catch/flag code behavior that is outside the types of behavior that you specify acceptable within a certain epoch.

What is a use case for request-based one-sided operations?
The text didn't go into very much detail here.
