# Review

## Chapter 10: Topologies

if you tell MPI the patterns of communication you will be using (e.g., graph connectivity between nodes) it can optimize where in hardware it places different processes so that communication between connected processes is fast

options:
* undefined
* cartesian (e.g., an X-d grid)
* graph ones (arbitrary graph topology)

cartesian
* can be wraparound

graph
* can specify by telling which other processes each process sends to/receives from or just sends to

neighbor collectives:
* looks like a neighbor MPI collective is automatically created for each process

## Chapter 11: Shared Memory

previously with windows: every process can access the window of every other process, even though there might be hardware differences under the hood that make some transfers much more efficient than others

you might want to exploit fast transfers where there's actual physical shared memory; use `MPI_Comm_split_type`
* user-level copying is possible, although it looks like MPI send/recieve calls should just do this under the hood 

# My Questions

What is `MPI_Cart_shift` useful for???
