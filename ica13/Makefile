all: data.csv

multiply_naive.out: get_walltime.h matrix_multiply.cpp
	c++ -std=c++14 -O3 -o multiply_naive.out matrix_multiply.cpp get_walltime.h
	chmod +x multiply_naive.out

data_naive.csv: multiply_naive.out
	rm -f data_naive.csv
	export OMP_NUM_THREADS=40 && ./multiply_naive.out data_naive.csv

multiply.out: get_walltime.h matrix_multiply.cpp
	c++ -std=c++14 -O3 -fopenmp -o multiply.out matrix_multiply.cpp get_walltime.h
	chmod +x multiply.out

data.csv: multiply.out
	rm -f data.csv
	export OMP_NUM_THREADS=40 && ./multiply.out data.csv

clean:
	rm -f *.out *.gch *.csv
