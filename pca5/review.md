# Review

available MPI bindings
* C/C++ (C++ style bindings deprecated)
* Fortran
* Python (third-party package)

SPMD (single program multiple data)
* 1990's: each node has a single processor
* today: each node has several chips (each with own socket) and multiple cores per chip
* each parallel run comprises many independently started MPI processes
* world = all available processors
* can define subsets of processors
* each processor knows own rank, total # of procs

use `MPI_Init` for initialization (forward command line arguments to it)


# Questions

The text states that ethernet is a mode of slow connection between nodes.
What modes of faster communication between nodes are available?
How much faster are they?
