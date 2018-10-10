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

    // now do non-blocking send/recieve
    MPI_Request* requests = (MPI_Request*)malloc( 2*sizeof(MPI_Request) );

    // send to left neighbor rank
    // tag with 0
    MPI_Isend(
        &x[1], /* buf */
        1, /* count */
        MPI_FLOAT, /* datatype */
        leftNeigh, /* dest */
        0, /* tag */
        MPI_COMM_WORLD, /* communicator */
        &requests[0] /* communication request */
      );

    // send to right neighbor rank
    // tag with 1
    MPI_Isend(
        &x[nLocal], /* buf */
        1, /* count */
        MPI_FLOAT, /* datatype */
        rghtNeigh, /* dest */
        1, /* tag */
        MPI_COMM_WORLD, /* communicator */
        &requests[0] /* communication request */
      );

    // perform the averaging on available values
    for (int i = 1; i < nLocal-1; ++i)
    {
        y[i] = (x[i]+x[i+1]+x[i+2])/3.;
    }

    // recieve from right neighbor rank
    // tagged with 0
    MPI_Irecv(
        &x[nLocal+1], /* buf */
        1, /* count */
        MPI_FLOAT, /* datatype */
        rghtNeigh, /* source */
        0, /* tag */
        MPI_COMM_WORLD, /* communicator */
        &requests[1] /* request */
      );

    // recieve from left neighbor rank
    // tagged with 1
    MPI_Irecv(
        &x[0], /* buf */
        1, /* count */
        MPI_FLOAT, /* datatype */
        leftNeigh, /* source */
        1, /* tag */
        MPI_COMM_WORLD, /* communicator */
        &requests[1] /* request */
      );

    MPI_Waitall(2,requests,MPI_STATUSES_IGNORE);

    // perform the averaging on recieved values
    y[0] = (x[0]+x[1]+x[2])/3.;
    y[nLocal] = (x[nLocal-1]+x[nLocal]+x[nLocal+1])/3.;

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
