all: exercise-8-2.log

exercise-8-2.out: exercise-8-2.cpp
	mpic++ --std=c++11 -o exercise-8-2.out exercise-8-2.cpp

exercise-8-2.log: exercise-8-2.out
	mpirun -n 3 exercise-8-2.out > exercise-8-2.log

clean:
	rm -f *.log *.out

.PHONY: clean
