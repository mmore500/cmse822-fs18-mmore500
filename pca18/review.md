# key points

parallelize first, vectorize second
* but vectorization is too important to ignore
* together, both are impressive!

assertion: we need to embrace explicit vectorization
* makes code more performance portable
* q: how to constrain your program so it vectorizes well
* problem: in C/C++ pointers can be aliased
  * that means you can be updating the vector you're reading in form
  * the in/out aren't necessarily independent parts of an array
  * need to use `restrict` keywords for vectorization

what is a vector?

vector instructions
* load nx elements
* do nx ops
* store nx results

how to get vectorization
1. use keywords and hope it compiles with vectorization
2. use `restrict` keyword
3. use `#pragma ivdep`
  * ignore assumed vector dependencies
  * might not be the necessary thing that's holding the compiler back from vectorization
4. "mandatory vectorization"
  * vs. tell compiler what it wants to hear so it feels safe to vectorize
  * just do it and debug later
  * `#pragma ompsimd`
5. SIMD instruction intrinsics
  * isn't portable
  * but is very malleable
6. array operations (Cilk TM plus)
  * challenge: long vector slices cause cache issues, need to keep slices short

x86 growth of instruction set is in vector instructions
* future is a combo of cleverer hardware and cleverer compilers

profiling!!!
* "vector advisor" GUI
* performance tuning tools are your friend... not just `printf`
* look for confirmation of your theory (test it) or for surprises

# exercises

## 1.

Consider the following simple loop.

```C
void v_add (float *c, float *a, float *b)
{
    for (int i = 0; i <= MAX; i++)
       c[i] = a[i] + b[i];
}
```

Is this loop SIMD-vectorizable automatically by the compiler?
Why or why not?

## response

At this point, it is not.
This is because, unlike Fortran, in C/C++ pointers can be aliased.
Potentially, some `c[i]` might correspond to an `a[j]` and/or `b[k]` such that we actually update one of the inputs.
That means, if we chunk through the array 4 or 8 or 16 at a time, we might use an un-updated input value so we could get an incorrect result.

If we could be assured `a`, `b`, and `c` all corresponded to distinct regions of memory we could vectorize without worry

## 2.

Can functions called within an OpenMP parallel region be vectorized?
Explain your answer.

## response

Yes!
I googled around and came upon this from the [IBM Knowledge Center](https://www.ibm.com/support/knowledgecenter/en/SSXVZZ_16.1.0/com.ibm.xlcpp161.lelinux.doc/compiler_ref/prag_omp_for_simd.html)

> #pragma omp for simd
##Purpose
The omp for simd directive distributes the iterations of one or more associated loops across the threads that already exist in the team and indicates that the iterations executed by each thread can be executed concurrently using SIMD instructions.

OpenMP allows work to be distributed over different threads, which then each use Single Instruction Multiple Data instructions (i.e., vectorize the processing).

# questions for class

Aren't speedup bar graphs a little misleading?
For example, if you have different changes that cause a 4x and a 3x speedup, respectively, whatever change you apply LAST will look larger in absolute terms.
