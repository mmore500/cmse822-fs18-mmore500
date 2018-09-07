all: data_naive.csv data_03.csv

multiply_naive.out: get_walltime.h matrix_multiply.cpp
	c++ -o multiply_naive.out matrix_multiply.cpp get_walltime.h
	chmod +x multiply_naive.out

multiply_03.out: get_walltime.h matrix_multiply.cpp
	c++ -03  -o multiply_03.out matrix_multiply.c get_walltime.h
	chmod +x multiply_03.out

data_naive.csv: multiply_naive.out
	rm -f data_naive.csv
	./multiply_naive.out data_naive.csv

data_03.csv: multiply_03.out
	rm -f data_03.csv
	./multiply_03.out data_03.csv

clean:
	rm -f *.out *.gch *.csv
