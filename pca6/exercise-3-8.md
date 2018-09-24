# Prompt

Let each process compute a random number.
You want to print the maximum value and on what processor it is computed.
What collective(s) do you use?
Write a short program.

# Response

I would use a `GATHER`.

```
float myrandom = (float) rand() / (float) RAND_MAX;
float result;

int target_proc = nprocs-1;

float* localrands;

if (procno==root)
  localrands = (float*) malloc( (nprocs+1)*sizeof(int) );

// everyone contributes their info
MPI_Gather(&localrand,1,MPI_FLOAT,localrands,1,MPI_FLOAT,root,comm);

auto maxit = std::max_element(localrands, localrands + nprocs + 1);

std::cout << "largest random value " << *maxit << std::endl;
std::cout << "whicn processor " << std::distance(localrands, maxit) << std::endl;
```
