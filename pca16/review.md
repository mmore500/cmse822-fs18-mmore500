# key points

## Synchronization

ways of telling threads to perform actions in a certain sequence

* `critical` only execute by one thread at a time
  * less efficient "mutual exclusion"
  * works by acquiring a lock
* `atomic` do read/write in one go
  *  relies on hardware support for atomic updates
    * more efficient "mutual exclusion"
* `barrier` everybody has to be done with previous work in order for anybody to continue
  * there are implicit barriers after load sharing constructs
* `ordered`
* `locks`
    * interesting use case: updating bins of histogram
* `flush` to be discussed later
* `nowait` skip barrier at the end of a for loop

## Tasks

* OpenMP uses this under the cover
* "block of work"
  * a section of code plus the data environment in which it occurred
  * will be executed later, as scheduled (by whim of task scheduler)
* do things besides loop/section
  * ex., while loop traversing a linked list

task data
* tasks get created at one time, executed at another
* global data is global
* private data becomes `firstprivate`
  * e.g., copied into thread's own space
  * preserves value that was current when task was created

synchronization
* use `taskwait` directive to explicitly indicate the join of forked tasks
* use `taskgroup`directive followed by structured block
  * waits on all tasks, including recursively tasks created recursively within the block
* use `depend` clause for tasks defining what read/write dependencies the task has
  * scheduler constructs dependency graph for you
  * ordering in time related to top/bottom linear organization of tasks (and indicated dependency vars)
  * four types of dependencies
    1. read after write
    2. write after read
    3. write after write
    4. read after read (can be run in other order)

scheduling points
* at a *task scheduling point* the thread may switch to execution of another task
* `taskwait` and `taskyield`
* look out for abandoned locks
* also, value of a thread-id might change

canceling tasks
* useful when performing a search

# questions for class

When would you use a nested lock?
The author doesn't give a use case.

The author gives an example where `nowait` has desired behavior because released threads work on same values within next for loop.
Would we be able to get similar consistency if the next for loop had a different number of iterations or iterated by a different step size?
