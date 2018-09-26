#include <iostream>
#include <stdlib.h>
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
    printf("processor name: %s\n",name);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    cout<<"my rank:"<<rank<<endl;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    cout<<"the size:"<<rank<<endl;


    char buffer [50];
    sprintf(buffer,"%d.log",rank);
    fprintf(fopen(buffer,"w+"),"writing to my own file!");

    if(rank==0){
      printf("special message from just the root: the size is %d.",size);
    }

    MPI_Finalize();

    cout<<"Hello, after finalize!"<<endl;

    return 0;
}
