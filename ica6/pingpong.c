#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char *argv[])
{
    const int ROOT = 0;

    double runtime;
    MPI_Init(&argc, &argv);

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srandom(rank + 1);            /* seed the random number generator */

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == ROOT) {
      printf("m, sec\n");
    }


    // send buffer
    char * send_buf = malloc(sizeof(char));
    char * recv_buf = malloc(sizeof(char));

    for(int m = 1; m <= 16777216; m *=2) {

    // free previous buff
    free(send_buf);
    free(recv_buf);

    // allocate new buff
    send_buf = malloc(sizeof(char) * m);
    recv_buf = malloc(sizeof(char) * m);

    runtime = MPI_Wtime();

    // ping pong forever!
    for(size_t n = 0; n < 100; ++n) {

    if (rank == ROOT) {
      // ping
      // printf("ping");

      MPI_Send(send_buf, m, MPI_CHAR, !rank, 0, MPI_COMM_WORLD);

      MPI_Recv(recv_buf, m, MPI_CHAR, !rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    } else {
      // pong;
      MPI_Recv(recv_buf, m, MPI_CHAR, !rank, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      // printf("pong");

      MPI_Send(send_buf, m, MPI_CHAR, !rank, 0, MPI_COMM_WORLD);
    }

  }

  runtime = MPI_Wtime() - runtime;

  if (rank == ROOT) {
    printf("%d, %f\n",m,runtime);
  }

  }


  MPI_Finalize();

  }
