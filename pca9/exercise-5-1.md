# Prompt

Suppose you have a matrix of size `4N \times 4N` and you want to send the elements `A[4*i][4*j]` with `i,j=0,...,N-1`.
How would you send these elements with a single transfer?

# Response

I would use a two-layered array type.
The first array type would pick up every fourth element in one of the inner arrays.
The second array type would have as its data type the first array type.
It would pick up every fourth element of the outer array (i.e., every fourth inner array).
