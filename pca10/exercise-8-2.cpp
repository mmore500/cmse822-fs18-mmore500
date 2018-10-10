#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <mpi.h>
#include <stdio.h>
#include <random>

int main(int argc, char *argv[])
{
  // for reproducibility
  srand(1);

  // Initialize the MPI communicator
  MPI_Init(&argc, &argv);

  // Get rank/size
  int myRank, numRanks;

  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &numRanks);

  MPI_Win the_window;
  int my_number = 10+myRank;
  int other_number = 0;

  MPI_Win_create(
      &other_number,  /* void *base */
      sizeof(int),    /* MPI_Aint size */
      sizeof(int),    /* int disp_unit */
      MPI_INFO_NULL,  /* MPI_Info info */
      MPI_COMM_WORLD, /* MPI_Comm comm */
      &the_window     /* MPI_Win *win */
    );

  MPI_Win_fence(0/* int assert */,the_window/* MPI_Win win */);

  if (myRank==0) {
    MPI_Put(
      &my_number,      /* const void *origin_addr */
      1,               /* int origin_count */
      MPI_INT,         /* MPI_Datatype origin_datatype */
      1 + rand() % 1,  /* int target_rank */
      0,               /* MPI_Aint target_disp */
      1,               /* int target_count */
      MPI_INT,         /* MPI_Datatype target_datatype */
      the_window       /* MPI_Win win */
    );
  }

  MPI_Win_fence(0/* int assert */,the_window/* MPI_Win win */);

  MPI_Win_free(&the_window);

  if (myRank!=0) {
    printf("%d got the following: %d\n", myRank, other_number);
  }

  MPI_Finalize();

  return 0;
}
