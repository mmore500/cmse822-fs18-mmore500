# Review

MPI collectives
* broadcast
* scatter
* reduction
  * to root
  * to all
  * operators:
    * MAX, MIN, SUM, PROD, ... (logical stuff), MAXLOC, MINLOC
    * you can also define your own
* gather
  * to root
  * to all
* all-to-all
  * i.e., simultaneous broadcast/gathers
* reduce-scatter
    * reduction of ON array of data, followed by scatter of data to individual processes
* barrier
  * not obviously useful
* scan
  * perform a reduction, but keep partial results

They implicitly synchronize.
* but sometimes not in the way you think (i.e., tricky example 3.13)

Variable-size-input variants available.
* i.e., each proc has a variable amount of data they want to share

Non-blocking variants are available (incl barrier)
* i.e., do own work while waiting for everyone else to catch up

time a message takes
* `\alpha + \beta n`
* `\alpha = latency`, `\beta = time-per-byte = (bandwidth)^{-1}`, `n = number of bytes sent`

can make broadcast distribution more efficient with a tree-based message chain


# Questions

What is an exclusive scan?
What's the difference compared to a partial scan?

Does using a "root" node truly deviate from `SPMD` in implementation (i.e., C code you write) or just conceptually in an informal discussion sense?
