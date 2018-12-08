all: data.csv

multiply_naive.out: get_walltime.h matrix_multiply.cpp
	g++ -std=c++14 -O0 -o multiply_naive.out matrix_multiply.cpp get_walltime.h
	chmod +x multiply_naive.out

data_naive.csv: multiply_naive.out
	rm -f data_naive.csv
	./multiply_naive.out data_naive.csv

multiply.out: get_walltime.h matrix_multiply.cpp
	g++ -std=c++14 -O3 -fopenmp -o multiply.out matrix_multiply.cpp get_walltime.h
	chmod +x multiply.out

data.csv: multiply.out
	rm -f data.csv
	./multiply.out data.csv

optimization-report: get_walltime.h matrix_multiply.cpp
	g++ -std=c++14 -fopt-info -O3 -o multiply.out matrix_multiply.cpp get_walltime.h > optimize-report-03.out

clean:
	rm -f *.out *.gch *.csv

.PHONY: optimization-report
