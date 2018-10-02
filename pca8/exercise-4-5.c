#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char *argv[])
{
    const int ROOT = 0;

    double runtime = MPI_Wtime();
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srandom(rank + 1);            /* seed the random number generator */

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // send buffer
    int * send_buf = malloc(sizeof(int));
    int * recv_buf = malloc(sizeof(int));

    // ping pong forever!
    while(1) {

    if (rank == ROOT) {
      // ping

      MPI_Send(send_buf, 1, MPI_INT, !rank, 0, MPI_COMM_WORLD);

      MPI_Recv(recv_buf, 1, MPI_INT, !rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      printf("ping!\n");

    } else {
      // pong
      MPI_Recv(recv_buf, 1, MPI_INT, !rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      printf("pong!\n");

      MPI_Send(send_buf, 1, MPI_INT, !rank, 0, MPI_COMM_WORLD);

    }

  }

  }
