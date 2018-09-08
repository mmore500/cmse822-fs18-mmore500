all: data_naive.csv data_O3.csv

multiply_naive.out: get_walltime.h matrix_multiply.cpp
	c++ -o multiply_naive.out matrix_multiply.cpp get_walltime.h
	chmod +x multiply_naive.out

multiply_O3.out: get_walltime.h matrix_multiply.cpp
	c++ -O3  -o multiply_O3.out matrix_multiply.cpp get_walltime.h
	chmod +x multiply_O3.out

data_naive.csv: multiply_naive.out
	rm -f data_naive.csv
	./multiply_naive.out data_naive.csv

data_O3.csv: multiply_O3.out
	rm -f data_O3.csv
	./multiply_O3.out data_O3.csv

clean:
	rm -f *.out *.gch *.csv
