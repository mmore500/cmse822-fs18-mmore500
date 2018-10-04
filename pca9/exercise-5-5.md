# Prompt

How would you describe the memory layout of a submatrix, if the whole matrix has size `M \times N` and the submatrix `m \times n`?

# Response

Let's assume C style row-major indexing (i.e., contiguous rows).

We would use an MPI array type.
The blocksize would be `n`, the number of columns of the submatrix (i.e., how long the rows of the submatrix are).
The stride would be `N`, the number of columns of the larger matrix (i.e., how long the rows of the larger matrix are).
The count would be `m`, the number of rows of the submatrix.
The initial pointer would point to the upper left entry of the submatrix in the matrix.
