#include <iostream>
#include <cstdlib>
#include <cmath>
#include <mpi.h>

int main(int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Check to make sure we have the argument for rowSize
    if (argc < 2)
    {
        if (rank == 0)
            std::cout << "Not enough arguments!" << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Let's initialize a "big" 2D array. For simplicity
    // each rank will hold one value for now.
    int myVal = rank;

    // Now, setup _two_ additional subcommunicators, one
    // for rows, one for columns:
    // 0 1 2
    // 3 4 5
    // 6 7 8
    // So that rowComms has {0,1,2}, {3,4,5}, {6,7,8}
    // and colComms has {0,3,6}, {1,4,7}, {2,6,8}
    // We do this by assigning the right "color" to the ranks

    // Now take command line argument to specify dimension of rows
    int rowSize = atoi(argv[1]);

    int rowColor = rank / rowSize; // PUT CODE HERE
    int colColor = rank % rowSize; // PUT CODE HERE

    std::cout << "rank: " << rank << " row/col: (" << rowColor << "," << colColor << ")" << std::endl;

    // Put a barrier after the print so everyone is together
    MPI_Barrier(MPI_COMM_WORLD);

    // Create column comm
    MPI_Comm colComm;
    MPI_Comm_split(
        MPI_COMM_WORLD, /* comm: communicator (handle) */
        colColor,       /* color: control of subset assignment (integer) */
        rowColor,       /* key: control of rank assigment (integer) */
        &colComm        /* newcomm: new communicator (handle) */
      );

    // Create row comm
    MPI_Comm rowComm;
    MPI_Comm_split(
        MPI_COMM_WORLD, /* comm: communicator (handle) */
        rowColor,       /* color: control of subset assignment (integer) */
        colColor,       /* key: control of rank assigment (integer) */
        &rowComm        /* newcomm: new communicator (handle) */
      );

    // Get the rank within the new communicators
    int rowRank, colRank;
    MPI_Comm_rank(rowComm, &rowRank);
    MPI_Comm_rank(colComm, &colRank);

    // Now perform reduction along rows and columns
    int rowSum, colSum;
    MPI_Reduce(
        &myVal, /* const void*sendbuf */
        &rowSum, /* void*recvbuf */
        1, /* int count */
        MPI_INT, /* MPI_Datatype datatype */
        MPI_SUM, /* MPI_Op op */
        0, /* int root */
        rowComm /* MPI_Comm comm */
      );
    MPI_Reduce(
        &myVal, /* const void*sendbuf */
        &colSum, /* void*recvbuf */
        1, /* int count */
        MPI_INT, /* MPI_Datatype datatype */
        MPI_SUM, /* MPI_Op op */
        0, /* int root */
        colComm /* MPI_Comm comm */
      );

    // Have the rank 0's in both comms print out the results
    if (rowRank==0)
    {
        std::cout << "Row " << rowColor << " rank 0: " << rank << ", sum:" << rowSum << std::endl;
    }
    if (colRank==0)
    {
        std::cout << "Col " << colColor << " rank 0: " << rank << ", sum:" << colSum << std::endl;
    }

    // call Finalize
    MPI_Finalize();

}
