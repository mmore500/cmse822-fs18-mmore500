# prompt

How would you determine whether a given program kernel is bandwidth or compute bound?

# response

Two possibilities:

1. Look at assembly code, calculate number of memory access operations versus number of total operations to determine arithmetical intensity, compare to a threshold.

2. Run on processor simulation (or on two different processors), test whether increasing memory bandwidth holding everything else constant increases performance.