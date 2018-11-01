#include <iostream>
#include <mpi.h>
using namespace std;

int main(int argc, char *argv[])
{

  int provided;

  MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
  // Get rank/size
  int myRank, numRanks;

  MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
  MPI_Comm_size(MPI_COMM_WORLD, &numRanks);

  #pragma omp parallel
  {
  if (myRank == 0) cout << "Hello, World!\n" << endl;
  }

  MPI_Finalize();

  return 0;
}
