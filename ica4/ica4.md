I worked with He Lyu on this assignment.

4. Now run the executuable `a.out` using the MPI parallel run command and explain the output:

```
$ mpiexec -n 4 ./a.out
```

Running this code, our output was:
```
Hello, world!
Hello, world!
Hello, world!
Hello, world!
```

Each process (i.e., due to `-n 4`) is contributing one of the `Hello, world!`'s.

5. Add the commands `MPI_Init` and `MPI_Finalize` to your code. Put three different print statements in your code: one before the init, one between init and finalize, and one after the finalize. Recompile and run the executable, both in serial and with `mpiexec`, and explain the output.

This is our output:
```
Hello, before init!
Hello, before init!
Hello, before init!
Hello, before init!
Hello, in the middle!
Hello, in the middle!
Hello, in the middle!
Hello, in the middle!
Hello, after finalize!
Hello, after finalize!
Hello, after finalize!
Hello, after finalize!
```

It appears that `MPI_Init` and `MPI_Finalize` are acting as barriers.
Nobody can print the middle before everyone's printed init and nobody can print finalize before everyone's printed finalize.
However, looking at the textbook and the MPI documentation, `MPI_Init` and `MPI_Finalize` do NOT act as barriers.
What we're seeing here is coincidence.

6. Complete Exercises 2.3, 2.4, and 2.5 in the Parallel Programing book.

Here's our output for 2.3:
```
Hello, before init!
Hello, before init!
Hello, before init!
Hello, before init!
Hello, in the middle!
dev-intel18
Hello, in the middle!
dev-intel18
Hello, in the middle!
dev-intel18
Hello, in the middle!
dev-intel18
Hello, after finalize!
Hello, after finalize!
Hello, after finalize!
```

For 2.4:
```
Hello, before init!
Hello, before init!
Hello, before init!
Hello, before init!
Hello, in the middle!
processor name: dev-intel18
my rank:2
the size:2
Hello, in the middle!
processor name: dev-intel18
Hello, in the middle!
Hello, in the middle!
my rank:0
the size:0
processor name: dev-intel18
processor name: dev-intel18
my rank:3
the size:3
my rank:1
the size:1
Hello, after finalize!
Hello, after finalize!
Hello, after finalize!
```

For 2.5:
```
Hello, before init!
Hello, before init!
Hello, before init!
Hello, before init!
Hello, in the middle!
processor name: dev-intel18
my rank:2
the size:2
Hello, in the middle!
processor name: dev-intel18
Hello, in the middle!
Hello, in the middle!
my rank:0
the size:0
processor name: dev-intel18
processor name: dev-intel18
my rank:3
the size:3
my rank:1
the size:1
Hello, after finalize!
Hello, after finalize!
special message from just the root: the size is 4.Hello, after finalize!
Hello, after finalize!
```

The code is in `ica4/hello.cpp`.

## What to turn-in

To your git repo, in the `ica4` directory, commit your final, working code for the above exercises and responses addressing the above questions. Your final write-up and code are due in one week, on 9/27.
