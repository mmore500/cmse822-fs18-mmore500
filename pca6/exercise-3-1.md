# Prompt

How would you realize the following scenarios with MPI collectives?
1. Let each process compute a random number.
You want to print the maximum of these numbers to your screen.
2. Each process computes a random number again.
Now you want to scale these numbers by their maximum.
3. Let each processor compute a random number.
You want to print on what processor the maximum value is computed.

# Response

1. I would use a `reduce` with the `max` operator.
2. I would use an `all-reduce` with the `max` operator, perform the scaling on each process, then use a `gather` to collect the scaled random numbers for i/o.
3. I would use a `gather` then, in the root process, then scan over the array of collected random numbers to find the index of the maximum random number.
