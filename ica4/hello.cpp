#include <iostream>
#include "mpi.h"
#include "stdio.h"


using namespace std;

int main(int argc, char **argv)
{

    cout<<"Hello, before init!"<<endl;

    MPI_Init(&argc, &argv);

    cout<<"Hello, in the middle!"<<endl;

    int resultlen = 0;
    char *name = (char*)malloc(sizeof(char)*MPI_MAX_PROCESSOR_NAME);
    int res = MPI_Get_processor_name(name, &resultlen);
    printf("%s\n",name);

    MPI_Finalize();

    cout<<"Hello, after finalize!"<<endl;

    return 0;
}
