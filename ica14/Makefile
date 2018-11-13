all: taskMMM.out

taskMMM.out: taskMMM.c
	c++ -std=c++14 -fopenmp -O3 -o taskMMM.out taskMMM.c
	chmod +x taskMMM.out

run: taskMMM.out
	export OMP_NUM_THREADS=10 && ./taskMMM.out

clean:
	rm -f *.out *.gch *.csv

.PHONY: run clean
