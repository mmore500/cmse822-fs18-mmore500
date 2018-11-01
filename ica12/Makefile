hello.out: hello.cpp
	mpic++ -fopenmp -o hello.out hello.cpp

clean:
	rm -f hello.out

run:
	mpirun -n 10 hello.out

.PHONY: clean run
