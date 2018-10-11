all: threePoint-n1.log threePoint-n2.log threePoint-n4.log

threePoint.out: threePoint.cpp
	mpic++ -o threePoint.out threePoint.cpp

threePoint-n1.log: threePoint.out
	mpirun -n 1 threePoint.out 10 > threePoint-n1.log

threePoint-n2.log: threePoint.out
	mpirun -n 2 threePoint.out 10 > threePoint-n2.log

threePoint-n4.log: threePoint.out
	mpirun -n 4 threePoint.out 10 > threePoint-n4.log

clean:
	rm -f *.out *.log
