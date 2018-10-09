all: create_struct.log mpi_subcommReduce.log

create_struct.out: create_struct.cpp
	mpic++ -std=c++11 -o create_struct.out create_struct.cpp

mpi_subcommReduce.out: mpi_subcommReduce.cpp
	mpic++ -std=c++11 -o mpi_subcommReduce.out mpi_subcommReduce.cpp

create_struct.log: create_struct.out
	mpirun -n 5 ./create_struct.out > create_struct.log

mpi_subcommReduce.log: mpi_subcommReduce.out
	mpirun -n 9 ./mpi_subcommReduce.out 3 > mpi_subcommReduce.log

clean:
	rm -f create_struct.log mpi_subcommReduce.log \
		create_struct.out mpi_subcommReduce.out

.PHONY: clean
