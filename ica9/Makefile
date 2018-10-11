all: threePoint-10-n1.log threePoint-10-n2.log threePoint-10-n4.log threePoint-13-n1.log threePoint-13-n2.log threePoint-13-n4.log

threePoint.out: threePoint.cpp
	mpic++ -o threePoint.out threePoint.cpp

threePoint-10-n1.log: threePoint.out
	mpirun -n 1 threePoint.out 10 > threePoint-10-n1.log

threePoint-10-n2.log: threePoint.out
	mpirun -n 2 threePoint.out 10 > threePoint-10-n2.log

threePoint-10-n4.log: threePoint.out
	mpirun -n 4 threePoint.out 10 > threePoint-10-n4.log

threePoint-13-n1.log: threePoint.out
	mpirun -n 1 threePoint.out 13 > threePoint-13-n1.log

threePoint-13-n2.log: threePoint.out
	mpirun -n 2 threePoint.out 13 > threePoint-13-n2.log

threePoint-13-n4.log: threePoint.out
	mpirun -n 4 threePoint.out 13 > threePoint-13-n4.log

clean:
	rm -f *.out *.log
