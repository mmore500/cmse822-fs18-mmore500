#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <mpi.h>
#include <vector>

int main(int argc, char *argv[])
{
    // Initialize the MPI communicator
    MPI_Init(&argc, &argv);

    // Get rank/size
    int myRank, numRanks;

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &numRanks);

    int nGlobal = atoi(argv[1]);

    // Setup local array
    int nLocal = (int)nGlobal/numRanks;
    if (myRank==0) nLocal += nGlobal%numRanks;

    // Allocate and initialize the vector
    // x is allocate with 2 ghost zones
    std::vector<float> x(nLocal+2);
    std::vector<float> y(nLocal);
    for (int i=1; i<nLocal+1; ++i){
        x[i] = i + myRank*(nLocal) + (!!myRank)*((nGlobal%numRanks));
    }

    // Now specify neighbors
    int leftNeigh = myRank-1;
    if (myRank==0) leftNeigh = numRanks-1;
    int rghtNeigh = myRank+1;
    if (myRank==numRanks-1) rghtNeigh = 0;

    // window setup
    MPI_Win low_window, high_window;
    MPI_Win_create(
        &x[0],           /* void *base */
        sizeof(float),   /* MPI_Aint size */
        sizeof(float),   /* int disp_unit */
        MPI_INFO_NULL,   /* MPI_Info info */
        MPI_COMM_WORLD,  /* MPI_Comm comm */
        &low_window      /* MPI_Win *win */
      );
    MPI_Win_create(
        &x[nLocal+1],    /* void *base */
        sizeof(float),   /* MPI_Aint size */
        sizeof(float),   /* int disp_unit */
        MPI_INFO_NULL,   /* MPI_Info info */
        MPI_COMM_WORLD,  /* MPI_Comm comm */
        &high_window     /* MPI_Win *win */
      );

    // do puts
    MPI_Win_fence(0/* int assert */,low_window/* MPI_Win win */);
    MPI_Win_fence(0/* int assert */,high_window/* MPI_Win win */);

    // put to left neighbor rank
    MPI_Put(
      &x[1],           /* const void *origin_addr */
      1,               /* int origin_count */
      MPI_FLOAT,       /* MPI_Datatype origin_datatype */
      leftNeigh,       /* int target_rank */
      0,               /* MPI_Aint target_disp */
      1,               /* int target_count */
      MPI_FLOAT,       /* MPI_Datatype target_datatype */
      high_window      /* MPI_Win win */
    );

    // put to right neighbor rank
    MPI_Put(
      &x[nLocal],      /* const void *origin_addr */
      1,               /* int origin_count */
      MPI_FLOAT,       /* MPI_Datatype origin_datatype */
      rghtNeigh,       /* int target_rank */
      0,               /* MPI_Aint target_disp */
      1,               /* int target_count */
      MPI_FLOAT,       /* MPI_Datatype target_datatype */
      low_window       /* MPI_Win win */
    );

    // perform the averaging on available values
    for (int i = 1; i < nLocal-1; ++i)
    {
        y[i] = (x[i]+x[i+1]+x[i+2])/3.;
    }

    // complete puts
    MPI_Win_fence(0/* int assert */,low_window/* MPI_Win win */);
    MPI_Win_fence(0/* int assert */,high_window/* MPI_Win win */);

    MPI_Win_free(&low_window);
    MPI_Win_free(&high_window);

    // perform the averaging on recieved values
    y[0] = (x[0]+x[1]+x[2])/3.;
    y[nLocal-1] = (x[nLocal-1]+x[nLocal]+x[nLocal+1])/3.;

    if (myRank == 0)
    {
      std::cout << "x[i]'s " << std::endl;
      std::cout << std::setw(10) << std::left << "rank"
        << std::setw(10) << std::left << "i"
        << std::setw(10) << std::left << "x[i]" << std::endl;
    }

    for (int j = 0; j < numRanks; j++)
    {
      if (myRank == j) {
        // sanity check
        for (int i = 0; i < nLocal + 2; i++)
        {
          std::cout << std::setw(10) << std::left << myRank
            << std::setw(10) << std::left << i
            << std::setw(10) << std::left << x[i] << std::endl;
        }
      }
      MPI_Barrier(MPI_COMM_WORLD);
    }

    if (myRank == 0)
    {
      std::cout << std::endl << "y[i]'s " << std::endl;
      std::cout << std::setw(10) << std::left << "rank"
        << std::setw(10) << std::left << "i"
        << std::setw(10) << std::left << "y[i]" << std::endl;
    }

    for (int j = 0; j < numRanks; j++)
    {
      if (myRank == j) {
      // print results
        for (int i = 0; i < nLocal; i++)
        {
          std::cout << std::setw(10) << std::left << myRank
            << std::setw(10) << std::left << i
            << std::setw(10) << std::left << y[i] << std::endl;
        }
      }
      MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();

}
