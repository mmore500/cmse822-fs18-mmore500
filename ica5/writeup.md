# ICA5 Writeup

Matthew Andres Moreno, working with Ian Whalen

## Question 1

Our implementation is at `ica5/par_pi_calc.c`.

## Question 2

Here are our results performing the same number of rounds on each rank.
(Thus, when more ranks are added, more rounds are performed).

| n  | rounds     | walltime    |
|----|------------|-------------|
| 1  | 1000       | 0.627225    |
| 2  | 1000       | 0.555165    |
| 3  | 1000       | 0.71577     |
| 4  | 1000       | 0.606528    |

It appears that `walltime` remains approximately constant.
Although there is more total work each time `n` increased, the amount of work added each time `n` is increased is proportional to the extra processing capability added to the parallel time.
This is something like adding another assembly line to a factory: more product is produced, but each assembly line still operates at the same rate so the time it takes to produce 1,00 widgets remans about the same.
In this case, it's the amount of time it takes each processor to perform 1,000 rounds that remains constant.
For VERY large `n`, we might expect walltime to start to increase noticeably as the MPI Reduce operation used to consolodiate each assembly line's estimate for pie gets more and more intense.

This question is addressing *weak scaling*, where the amount of work increases in lockstep with increases in the parallelism.

## Question3

Here are our results dividing up 1,000 rounds over 1, 2, 3, and 4 ranks.
(When more ranks are added, the total number of rounds performed remains the same).

| n  | rounds     | walltime    |
|----|------------|-------------|
| 1  | 1000       | 0.232601    |
| 2  | 1000       | 0.538918    |
| 3  | 1000       | 0.432371    |
| 4  | 1000       | 0.380431    |

It appears that `walltime` is actually lowest for `n=1` (one mpi worker).
`walltime` jumps up at `n=2`, perhaps due to the addition of communication overhead (`n=1` requires communication between processors because there's only one processor).
Then, `walltime` decreases for `n=3` and decreases further for `n=4` as more processors are thrown at the problem.
For `n=4`, for example, each processor only needs to handle 250 rounds.
This is half as many rounds as each processor needed to handle at `n=2', when each processor was responsible for 500 rounds.

The discontinuity between `n=1` and `n=2` seems to be a very interesting result that exposes the cost of parallelism overhead, suggesting that for this small problem size it actually *outweighs* the gains from parallelism.
However, it is also possible that the very quick runtime at `n=1` is a bit of an outlier.
Above, when one processor executed 1000 rounds, it took 0.6 seconds (not 0.2 seconds).
The code should have executed very much the same for `n=1` whether the rounds were nominally "shared" between the one process or set at 1,000 for that process.
In order to more substinatively profile performance, we would want to perform many replicates of each condition to account for this kind of noise.

This question is addressing *strong scaling*, where the amount of work stays constant as we increase the amount of parallelism we're using.

## Question 4

The raw and plotted results from our strong scaling study, looking at how throwing increased parallelism with constant problem size, are included below. a strong scaling study on HPCC with processor counts of 1, 2, 4, 8, 16, 32, and 64. For this, use non-interactive jobs and modify the jobsubmit.sb script as necessary. Make a plot of your scaling results and turn it in along with your code. Give a brief explanation of your results and plot.

We performed our experiments using 1e3, 1e6, and 1e9 rounds instead of darts.
Rounds were split between processors.
The gist is the same: for a large (i.e., 1e9 rounds), medium (i.e., 1e6), and small (i.e., 1e3) problem size, test how adding more processors affects wall time.

![plot](ica5/results.png)

| n  | rounds     | walltime    |
|----|------------|-------------|
| 64 | 1000       | 2.153208    |
| 64 | 1000000    | 2.587077    |
| 64 | 1000000000 | 149.369626  |
| 32 | 1000000000 | 164.618104  |
| 32 | 1000000    | 2.121824    |
| 32 | 1000       | 14.090727   |
| 16 | 1000       | 0.940628    |
| 16 | 1000000    | 2.095373    |
| 16 | 1000000000 | 283.96766   |
| 8  | 1000000000 | 604.817775  |
| 8  | 1000000    | 1.136926    |
| 8  | 1000       | 0.794475    |
| 4  | 1000000000 | 1167.55187  |
| 4  | 1000000    | 1.772841    |
| 4  | 1000       | 0.380431    |
| 2  | 1000000000 | 2043.854222 |
| 2  | 1000000    | 18.223021   |
| 2  | 1000       | 0.538918    |
| 1  | 1000000000 | 4464.842125 |
| 1  | 1000000    | 5.268386    |
| 1  | 1000       | 0.232601    |

For small problem size (1e3 rounds), increasing `n` actually inceases walltime.
This is because the parallelism overhead actually outweighs the speedup gained by divvying up the small amount of work.

For medium problem size (1e6 rounds), increasing `n` seems to trend to decrease walltime, but the trend is noisy and week.
This is because the problem is large enough that the speedup gained by divvying up the work is comparable to the parallelism overhead.

For large problem size (1e9 rounds), increasing `n` very clearly decreases walltime.
On the log=log plot, the trend is very clearly linear for the smaller `n`.
This indicates that a near-ideal speedup is being achieved.
As `n` approaches 64, though the linear trend seems to level off a bit.
I would eventually expect the `walltime` to asymptote as `n` is further increased.
This reflects the fact that, for this large but finite problem size, the gains from parallelism are still limited.
