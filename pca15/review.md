# key points

## Work Sharing

*parallel region* `->` team of threads

work sharing constructs: a way of dividing parallelizable work over a team of threads
* `for/do` divide up the loop iterations
* `sections` divide up a fixed number of sections
  * each section is numbered
  * you can use a reduction to combine results of individual sections
* `single` executed by a single thread
  * implicit barrier after this section
  * `master` has no implicit barrier
* `task`
* `workshare` parallelize Fortran array syntax

## Controlling Thread Data

two types of data in a parallel region
* private
  * declared in a block following an OpenMP directive
  * different stack per thread
* shared
  * any data declared outside

calling functions from within the parallel region
* fall within the dynamic scope of that region
* static variables are shared
* function arguments inherit status from calling environment

remember to declare temporaries as private within a loop!

you can declare private/shared directly in the pragma directive
* `none` option is good for debugging... specify for each variable whether private or shared

dynamically allocated data can only be shared

`threadprivate`: private data which is not limited in lifetime to one parallel region
* use `copyin` clause if you want to initialize all identically
* e.g., random number generator

## Reductions

naive methods to combine results from individual threads can lead to race conditions

simple solution: declare an `omp critical` section

MPI reductions: useful in loops
* combined following end of lop

if you try to do this manually by having each thread write to its own spot in an array, you can run into false sharing
* keep having to update cache because in same cacheline


built-in reduction operators:
* `+`
* `*`
* `-`
* `max`
* `min`
* `&`
* `&&`
* `|`
* `||`
* `^`

user-defined reductions and reductions with a user-defined initial value are possible

apparently, there can be some rounding weirdness for floating-point reductions

# questions for class

For `sections`, why are reductions advantageous over just using temporary variables?

Why is the `firstprivate` only defined for Fortran and is not available for C?
